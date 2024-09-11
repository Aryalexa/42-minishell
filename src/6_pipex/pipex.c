/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/11 13:11:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

/**
 * changes the node cmd to its full path.
 * return 1 when resolved, 0 if error
 * supported:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * 
 */
int	solve_path(t_cmdnode *node, char *env[])
{
	char		*cmd_path;	

	if (!node->cmd)
		return (0);
	if (node->cmd[0] == '/')
		return (1);
	else
	{
		if (check_builtin(*node) >= 0)
			return (1);
		cmd_path = find_path(node->cmd, env);
		if (!cmd_path)
		{
			my_perror_arg("command not found 🌸", node->cmd);
			return (0);
		}
		free(node->cmd);
		node->cmd = cmd_path;
		return (1);
	}
}

int	exec_builtin(t_cmdnode node, t_shcontext *env)
{
	int			i;
	const t_FP	built_ins[7] = {&exec_echo, &exec_exit,
		&exec_pwd, &exec_export, &exec_unset, &exec_env, &exec_cd};

	i = check_builtin(node);
	if (i >= 0)
		built_ins[i](node, env);
	return (0);
}

/**
 * infile? then file is new in
 */
void	process_infiles(int n, t_infile	*infiles)
{
	int			j;
	int			fdin;

	j = 0;
	while (j < n)
	{
		if (infiles[j].type == F_HEREDOC)
			infiles[j].fd = here_doc(infiles[j].filename_delim);
		j++;
	}
	j = 0;
	while (j < n)
	{
		if (infiles[j].type == F_HEREDOC)
		{
			dup2(infiles[j].fd, STDIN_FILENO);
			close(infiles[j].fd);
		}
		else
		{
			fdin = open(infiles[j].filename_delim, O_RDONLY);
			if (fdin < 0)
				my_perror_exit("*input file error at open");
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		j++;
	}
}
/**
 * outfile? then file new out
 */
void	process_outfiles(int n, t_outfile *outfiles)
{
	int	j;
	int	fdout;

	j = 0;
	while (j < n)
	{
		if (outfiles[j].type == F_APPEND)
			fdout = open(outfiles[j].filename,
					O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fdout = open(outfiles[j].filename,
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fdout < 0)
			my_perror_exit("error at open an outfile");
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		j++;
	}
	debug("exit outfiles\n");
}

int	process_and_execs(t_cmdnode node, t_shcontext *env)
{
	process_infiles(node.redir.n_in, node.redir.infiles);
	process_outfiles(node.redir.n_out, node.redir.outfiles);

	debug_str("ARGV 0:", node.argv[0]); //
	if (check_builtin(node) >= 0)
		return (exec_builtin(node, env)); //TODO
	else
	{
		execve(node.cmd, node.argv, (char *const *)env->env);
		return (0);
	}
}

/**
 * 	process files and pipes (if files, use files!)	
 */
void	my_exec(t_cmdnode node, t_shcontext *env)
{
	int	pipefd[2];
	int	pid;
	int	status;

	debug_str("executing", node.cmd); //
	if (pipe(pipefd) == -1)
		my_perror_exit("pipe failed");
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{
		// lectura: pipe con contenido
		// escritura SDTOUT
		debug("child execs"); //
		close(pipefd[0]);
		if (!node.last_node)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status = process_and_execs(node, env);
		exit(status);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		// if (wait(&status) == -1)
		// 	my_perror_exit("wait error");
		//if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		//	return ;
	}
}

/**
 * execute
 * it marks the last node
 */
void	run_exec(int n_nodes, t_cmdnode nodes[], t_shcontext *env)
{
	int	i;
	int	default_in;
	int	default_out;

	default_in = dup(STDIN_FILENO);
	default_out = dup(STDOUT_FILENO);
	i = 0;
	if (n_nodes == 1 && check_builtin(nodes[i]) >= 0)
		process_and_execs(nodes[i], env);
	else
	{
		while (i < n_nodes)
		{
			debug_int("new node-------------------", i); //
			if (i == n_nodes - 1)
				nodes[i].last_node = 1;
			if (solve_path(&(nodes[i]), env->env))
				my_exec(nodes[i], env);
			i++;
		}
		while (wait(NULL) > 0);
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
	debug("exit pipex\n");
}

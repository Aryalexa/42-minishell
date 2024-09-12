/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/12 18:14:22 by msoriano         ###   ########.fr       */
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
 * return bool: 1 when resolved, 0 if error
 * supported:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * 
 */
int	solve_path(t_cmdnode *node, char *env[], int *status)
{
	char		*cmd_path;	

	if (!node->cmd)
		return (1);
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
			*status = 127;
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
		return (built_ins[i](node, env));
	return (0);
}

/**
 * infile? then file is new in
 */
int	process_infiles(int n, t_infile	*infiles)
{
	int			j;
	int			fdin;

	j = 0;
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
				return (my_perror("*input file error at open"), 1);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		j++;
	}
	return (0);
}
/**
 * outfile? then file new out
 */
int	process_outfiles(int n, t_outfile *outfiles)
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
		{
			my_perror("error at open an outfile");
			return (1);
		}
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		j++;
	}
	debug("exit outfiles\n");
	return (0);
}

int	process_and_execs(t_cmdnode node, t_shcontext *env)
{
	int st;

	st = process_infiles(node.redir.n_in, node.redir.infiles);
	if (st != 0)
		return (st);
	st = process_outfiles(node.redir.n_out, node.redir.outfiles);
	if (st != 0)
		return (st);
	debug_str("ARGV 0:", node.argv[0]); //
	if (check_builtin(node) >= 0)
	{
		st = exec_builtin(node, env);
		debug_int("builtin status", st);
		return (st); //TODO
	}
	else
	{
		debug_str("cmd:", node.cmd);
		execve(node.cmd, node.argv, (char *const *)env->env);
		return (0);
	}
}

/**
 * 	process files and pipes (if files, use files!)	
 */
void	my_exec(t_cmdnode *node, t_shcontext *env)
{
	int	pipefd[2];
	int	pid;
	int	status;

	debug_str("executing", node->cmd); //
	if (pipe(pipefd) == -1)
		my_perror_exit("pipe failed");
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{
		debug("child execs"); //
		close(pipefd[0]);
		if (!node->last_node)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status = process_and_execs(*node, env);
		debug_str("? - Command:", node->cmd); //
		debug_int("? --->Status", status); //
		exit(status);
	}
	else
	{
		node->pid = pid;	
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		// if (wait(&status) == -1)
		// 	my_perror_exit("wait error");
		//if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		//	return ;
	}
}


void process_heredocs(int n_nodes, t_cmdnode *nodes)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_nodes)
	{
		debug_int("NODO:", i);
		j = 0;
		while (j < nodes[i].redir.n_in)
		{
			if (nodes[i].redir.infiles[j].type == F_HEREDOC)
			{
				nodes[i].redir.infiles[j].fd
					= here_doc(nodes[i].redir.infiles[j].filename_delim);
			}
			j++;
		}
		i++;
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
	int	status;

	status = 0;
	default_in = dup(STDIN_FILENO);
	default_out = dup(STDOUT_FILENO);
	i = 0;

	process_heredocs(n_nodes, nodes);
	if (n_nodes == 1 && check_builtin(nodes[i]) >= 0)
		env->status = process_and_execs(nodes[i], env);
	else
	{
		while (i < n_nodes)
		{
			debug_int("new node-------------------", i); //
			if (i == n_nodes - 1)
				nodes[i].last_node = 1;
			if (solve_path(&(nodes[i]), env->env, &status))
				my_exec(&(nodes[i]), env);
			i++;
		}
		i = 0;
		while (i < n_nodes)
		{
			waitpid(nodes[i].pid, &status, 0);
			debug_str("wait - Command:", nodes[i].cmd); //
			debug_int("wait - PID:", nodes[i].pid);
			debug_int("wait - Status:", status);
			i++;
		}
		env->status = status % 255;
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
	debug("exit pipex\n");//
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 18:33:25 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

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

/**
 * Process infiles, outfiles and execution.
 * @return exit status
 */
int	process_and_execs(t_cmdnode node, t_shcontext *env)
{
	int	st;

	st = process_infiles(node.redir.n_in, node.redir.infiles);
	if (st != 0)
		return (st);
	st = process_outfiles(node.redir.n_out, node.redir.outfiles);
	if (st != 0)
		return (st);
	if (check_builtin(node) >= 0)
	{
		st = exec_builtin(node, env);
		return (st);
	}
	else
	{
		debug_str("cmd:", node.cmd);
		if (node.cmd)
			execve(node.cmd, node.argv, (char *const *)env->env);
		return (env->status);
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

	if (pipe(pipefd) == -1)
		my_perror_exit("pipe failed");
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{
		signal_child();
		debug("🌵EXE child - signal_child"); //
		close(pipefd[0]);
		if (!node->last_node)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		status = process_and_execs(*node, env);
		exit(status);
	}
	else
	{
		signal_father();
		debug("🌵EXE parent - signal_father"); //
		node->pid = pid;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
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
	if (!process_heredocs(n_nodes, nodes, env))
		return ;
	if (n_nodes == 1 && check_builtin(nodes[0]) >= 0)
		env->status = process_and_execs(nodes[0], env);
	else
	{
		i = 0;
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
			debug_int("wait - Status:", status); //
			i++;
		}
		debug_int("🐥status after wait BEFORE: ", status); //
		env->status = get_signal_status(status) % 255;
		debug_int("🐥status after wait: ", env->status); //
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
}

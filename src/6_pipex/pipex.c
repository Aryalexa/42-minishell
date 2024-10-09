/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 20:02:29 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

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

	if (pipe(pipefd) == -1)
		my_perror_exit("pipe failed");
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{
		signal_child();
		close(pipefd[0]);
		if (!node->last_node)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(process_and_execs(*node, env));
	}
	else
	{
		signal_father();
		node->pid = pid;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

void	exec_pipe_loop(int n_nodes, t_cmdnode nodes[], t_shcontext *env,
	int *status)
{
	int	i;

	i = 0;
	while (i < n_nodes)
	{
		if (i == n_nodes - 1)
			nodes[i].last_node = 1;
		if (solve_path(&(nodes[i]), env->env, status))
			my_exec(&(nodes[i]), env);
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
	if (!process_heredocs(n_nodes, nodes, env))
		return ;
	if (n_nodes == 1 && check_builtin(nodes[0]) >= 0)
		env->status = process_and_execs(nodes[0], env);
	else
	{
		exec_pipe_loop(n_nodes, nodes, env, &status);
		signal_ignore();
		i = -1;
		while (++i < n_nodes)
			waitpid(nodes[i].pid, &status, 0);
		signal_father();
		env->status = get_real_exit_status(status) % 255;
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
}

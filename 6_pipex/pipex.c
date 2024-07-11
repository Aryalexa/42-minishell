/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/11 11:54:16 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
//#include <sys/types.h>
#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>



/**
 * diferenciar entre:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * - argv[0] falta
 * 
 */
void	my_exec(t_cmdnode node, char *env[])
{
	char		*cmd_path;
	const t_FP	built_ins[1] = {&exec_echo};
	const char	built_ins_names[7][7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	int			i;

	if (node.cmd[0] == '/')
		execve(node.cmd, node.argv, (char *const *)env);
	// cmd null ???
	else
	{
		i = 0;
		while (i < 7)
		{
			if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
			{
				built_ins[i](node, env);
				return ;
			}
			i++;
		}
		cmd_path = find_path(node.cmd, env);

		if (!cmd_path)
			exit(1); //my_exit("command path not found");
		execve(cmd_path, node.argv, (char *const *)env);
	}
}

/**
 * it creates a pipe so the output of the command is redirected to the pipe, 
 * and the parent can have access to it. The parent should set the read from 
 * the pipe by default, so the next execution reads from it. The parent should 
 * wait for child to terminate, so it is finished before more commands execute.
 * child: > pipe, exec
 * parent: < pipe, wait
*/
void	my_piped_exec(t_cmdnode node, char *env[])
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		exit(1); //my_exit("pipe could not be created");
	pid = fork();
	if (pid < 0)
		exit(1); //my_exit("fork error");
	if (pid == 0)
	{
		close_and_dup(pipefd, 1);
		my_exec(node, env);
	}
	else
	{
		close_and_dup(pipefd, 0);
		if (wait(&status) == -1)
			my_exit("wait error");
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			exit(1);////printerr_cur_cmd(node.cmd); // error handlingmy_exit("child did not success");
		}
	}
}

void	process_infiles(int n, t_infile	*infiles)
{
	int			j;
	int			fdin;

	///// save heredoc fds
	j = 0;
	while (j < n)
	{
		if (infiles[j].type == F_HEREDOC)
			infiles[j].fd = here_doc(infiles[j].filename_delim);
		j++;
	}
	/////
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
				my_exit("*input file error at open");
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		j++;
	}
}

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
			my_exit("error at open an outfile");
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		j++;
	}
}

void	my_pipex(int n_nodes, t_cmdnode nodes[], char *env[])
{
	int	i;

	i = 0;
	while (i < n_nodes)
	{
		process_infiles(nodes[i].redir.n_in, nodes[i].redir.infiles);
		process_outfiles(nodes[i].redir.n_out, nodes[i].redir.outfiles);

		my_exec(nodes[i], env);
		i++;
	}
}

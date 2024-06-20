/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/13 13:25:24 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
//#include <sys/types.h>
#include "../libft/libft.h"
#include "../main/minishell.h"
#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

/**
 * diferenciar entre:
 * - ruta relativa o absoluta (empieza con /)
 * - si es comando built-in o no
 * 
 */
void	my_exec(t_node node, char *env[])
{
	char	*cmd_path;

	cmd_path = find_path(node.cmd, env);
	if (!cmd_path)
	{
		// free??
		printerr_cur_cmd(node.cmd);
		my_exit("command path not found");
	}
	execve(node.cmd, node.argv, (char *const *)env);
	my_exit("exec error");
}

/**
 * it creates a pipe so the output of the command is redirected to the pipe, 
 * and the parent can have access to it. The parent should set the read from 
 * the pipe by default, so the next execution reads from it. The parent should 
 * wait for child to terminate, so it is finished before more commands execute.
 * child: > pipe, exec
 * parent: < pipe, wait
*/
void	my_piped_exec(t_node node, char *env[])
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		my_exit("pipe could not be created");
	pid = fork();
	if (pid < 0)
		my_exit("fork error");
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
			printerr_cur_cmd(node.cmd);
			my_exit("child did not success");
		}
	}
}

void	process_infiles(int n, t_infile	*infiles)
{
	int	j;
	int	fdin;

	j = 0;
	while (j < n)
	{
		if (infiles[j].type == F_HEREDOC)
		{
			//heredoc!
		}
		else
		{
			fdin = open(infiles[j].filename, O_RDONLY);
			if (fdin < 0)
				my_exit("input file error at open");
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		j++;
	}
}

void	my_pipex(t_node nodes[], char *envp[])
{
	int	i;
	int	j;

	i = 0;
	while (&nodes[i])
	{
		i++;
	}
}

void	my_pipex2(char *infile, char *outfile, char *cmds[], char *envp[])
{
	int		fdin;
	int		fdout;
	int		i;

	fdin = open(infile, O_RDONLY);
	if (fdin < 0)
		my_exit("input file error at open");
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	i = 0;
	while (cmds[i] && cmds[i + 1])
		my_piped_exec2(cmds[i++], envp);
	fdout = open(outfile, O_RDWR | O_CREAT, 0777);
	if (fdout < 0)
		my_exit("output file error at open");
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	my_exec2(cmds[i], envp);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	t_files files;

	if (argc >= 2)
		my_pipex(files, &argv[1], envp);
}
*/

int	main(int argc, char *argv[], char *envp[])
{
	char	*outfile;

	if (argc >= 5)
	{
		outfile = argv[argc - 1];
		argv[argc - 1] = NULL;
		my_pipex(argv[1], outfile, &argv[2], envp);
	}
	else
		ft_printf("Usage: ./pipex infile cmd1 cmd2 [.. cmdn] outfile");
}

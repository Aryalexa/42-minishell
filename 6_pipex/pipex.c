/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/16 13:57:26 by macastro         ###   ########.fr       */
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


void	child_executes(char *cmd_path, char *argv[], char *env[])
{
	int	pid;
	int	status; // salida!!

	pid = fork();
	if (pid == -1)
		perror_exit("error: fork failed.");
	if (pid == 0)
		execve(cmd_path, argv, (char *const *)env);
	else
		wait(&status);
}

/**
 * diferenciar entre:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * - argv[0] falta
 * 
 */
void	my_exec(t_cmdnode node, char *env[])
{
	int			i;
	char		*cmd_path;
	const t_FP	built_ins[2] = {&exec_echo, &exec_exit};
	const char	built_ins_names[7][7] = {"echo", "exit", "pwd",
		"export", "unset", "env", "cd"};

	debug("-- begin execution --\n");
	if (!node.cmd)
		return ;
	if (node.cmd[0] == '/')
		child_executes(node.cmd, node.argv, env);
	else
	{
		i = 0;
		while (i < 7) // number of builtins
		{
			if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
			{
				built_ins[i](node, env);
				return ;
			}
			i++;
		}
		ft_printf("executing %s \n", node.cmd);
		cmd_path = find_path(node.cmd, env);

		if (!cmd_path)
		{
			my_perror("command path not found 🌸");
			return ;
		}
		child_executes(cmd_path, node.argv, env);
		free(cmd_path);
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
	debug("exit infiles\n");

}

void	process_outfiles(int n, t_outfile *outfiles)
{
	int	j;
	int	fdout;

	j = 0;
	ft_printf("#outfiles: %i\n", n);
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
	debug("exit outfiles\n");
}

void	my_pipex(int n_nodes, t_cmdnode nodes[], char *env[])
{
	int	i;
	int	default_in;
	int	default_out;

	default_in = dup(STDIN_FILENO);
	default_out = dup(STDOUT_FILENO);
	i = 0;
	while (i < n_nodes) // node1 | node2
	{
		// process files and pipes (if files, use files!)
		process_infiles(nodes[i].redir.n_in, nodes[i].redir.infiles);
		process_outfiles(nodes[i].redir.n_out, nodes[i].redir.outfiles);
		if (i + 1 < n_nodes && nodes[i].redir.n_out == 0)
		{
			//pipe 
		}
		my_exec(nodes[i], env);
		dup2(default_in, STDIN_FILENO); // reset only when....
		dup2(default_out, STDOUT_FILENO); //
		i++;
	}
	debug("exit pipex\n");
}

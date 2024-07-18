/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 16:39:46 by msoriano         ###   ########.fr       */
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

void	child_executes(t_cmdnode node, char *env[])
{
	int pipefd[2];
	int	pid;
	int	status; // salida!!

    if (pipe(pipefd)  == -1)
        my_perror_exit("pipe failed");
    // dup2(fd[0], STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		my_perror_exit("error: fork failed.");
	if (pid == 0)
	{

        // lectura: pipe con contenido
        // escritura SDTOUT
		debug("child execs");
        // char * buff[2000];
		// read(0, buff, 45);
		// debug("read done");
		// write(2, buff, 45);
		// debug("write done");
		// write(1, "salida\n", 7);
        close(pipefd[0]);
		if(!node.last_node)
            dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(node.cmd, node.argv, (char *const *)env);
	}
	else
	{
        close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		debug("parent waiting");
		if (wait(&status) == -1)
			my_perror_exit("wait error");
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			my_perror_exit("child did not success");

		debug("parent waited!");
	}
}

int	cmd_is_builtin_exec(t_cmdnode node, char *env[])
{
	int			i;

	const t_FP	built_ins[2] = {&exec_echo, &exec_exit};
	const char	built_ins_names[7][7] = {"echo", "exit", "pwd",
		"export", "unset", "env", "cd"};
	i = 0;
	while (i < 7) // number of builtins
	{
		if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
		{
			built_ins[i](node, env);
			return (1);
		}
		i++;
	}
	return (0);
}


void	my_exec(t_cmdnode node, char *env[])
{
	debug("-- begin execution --\n");
	//if (cmd_is_builtin_exec(node, env))
		// 	return ;
	debug_str("executing", node.cmd);
	child_executes(node, env);
}
/**
 * diferenciar entre:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * - argv[0] falta
 * 
 */
int	solve_path(t_cmdnode *node, char *env[])
{
	char		*cmd_path;
	char		*aux;
	

	debug("-- solve path --");
	debug_str("cmd 1 ", (*node).cmd);
	debug_str("cmd 2", (node)->cmd);
	if (!node->cmd)
		return (0);
	if (node->cmd[0] == '/')
		return (1);
	else
	{
		// if (cmd_is_builtin_exec(node, env))
		// 	return ;
		//ft_printf("executing %s \n", node.cmd);
		cmd_path = find_path(node->cmd, env);
		if (!cmd_path)
		{
			my_perror("command path not found 🌸");
			return (0);
		}
		debug_str("cmd", node->cmd);
		aux = node->cmd;
		node->cmd = cmd_path;
		free(aux);
		debug_str("cmd", node->cmd);
		return (1);
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
			exit(1);
			//printerr_cur_cmd(node.cmd); 
			//error handlingmy_exit("child did not success");
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


void	print_nodes_2(t_cmdnode *nodes, int n)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("#nodes %i----\n", n);
	while (i < n)
	{
		ft_printf("nodes #%i\n", i);
		// cmd
		if (nodes[i].cmd)
			ft_printf("cmd:%s\n", nodes[i].cmd);
		else
			ft_printf("no cmd\n");
		// args
		j = 0;
		while (j < nodes[i].argc)
		{
			ft_printf("arg %i:%s\n", j, nodes[i].argv[j]);
			j++;
		}
		// redirs in
		j = 0;
		while (j < nodes[i].redir.n_in)
		{
			ft_printf("inf %i:%s", j, nodes[i].redir.infiles[j].filename_delim);
			if (nodes[i].redir.infiles[j].type == F_HEREDOC)
				ft_printf("(<<)\n");
			else if (nodes[i].redir.infiles[j].type == F_IN)
				ft_printf("(<)\n");
			else
				ft_printf("error\n");
			j++;
		}
		// redirs out
		j = 0;
		while (j < nodes[i].redir.n_out)
		{
			ft_printf("outf %i:%s", j, nodes[i].redir.outfiles[j].filename);
			if (nodes[i].redir.outfiles[j].type == F_APPEND)
				ft_printf("(>>)\n");
			else if (nodes[i].redir.outfiles[j].type == F_OUT)
				ft_printf("(>)\n");
			else
				ft_printf("error\n");
			j++;
		}
		i++;
	}
}

void	my_pipex(int n_nodes, t_cmdnode nodes[], char *env[])
{
	int	i;
	int	default_in;
	int	default_out;
	// int fd[2];

	default_in = dup(STDIN_FILENO);
	default_out = dup(STDOUT_FILENO);
	(void)env;
	i = 0;
	print_nodes_2(nodes, n_nodes);
	while (i < n_nodes) // node1 | nodeUlt
	{
		
		debug_int("new node-------------------", i);
		debug_str("cmd 01", nodes[i].cmd);
		if (i == n_nodes - 1)
			nodes[i].last_node = 1;
		debug_str("cmd 02", nodes[i].cmd);
		
		if (solve_path(&(nodes[i]), env))
			my_exec(nodes[i], env);

		// process files and pipes (if files, use files!)
		// process_infiles(nodes[i].redir.n_in, nodes[i].redir.infiles); // infile? file is new in
		// process_outfiles(nodes[i].redir.n_out, nodes[i].redir.outfiles); // outfile? file new out
		
		
		i++;
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
	debug("exit pipex\n");
}

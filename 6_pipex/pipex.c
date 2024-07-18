/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:37:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 19:39:52 by msoriano         ###   ########.fr       */
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

void	child_executes(t_cmdnode node, char *env[])
{
	int pipefd[2];
	int	pid;
	int	status; // salida!!

	// process files and pipes (if files, use files!)
	
		
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
        
        close(pipefd[0]);
		if(!node.last_node)
            dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		process_infiles(node.redir.n_in, node.redir.infiles); // infile? file is new in
		process_outfiles(node.redir.n_out, node.redir.outfiles); // outfile? file new out
		debug_str("ARGV 0:", node.argv[0]);
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
		//if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		//	return ;
		debug("parent waited!");
	}
}


int	check_builtin(t_cmdnode node)
{
	int			i;

	const char	built_ins_names[7][7] = {"echo", "exit", "pwd",
		"export", "unset", "env", "cd"};
	i = 0;
	while (i < 7) // number of builtins
	{
		if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(t_cmdnode node, char *env[])
{
	int			i;

	const t_FP	built_ins[7] = {&exec_echo, &exec_exit, 
		&exec_pwd, &exec_export, &exec_unset, &exec_env, &exec_cd};
	i = check_builtin(node);
	if(i >= 0)
		built_ins[i](node, env);
	return (0);
}


void	my_exec(t_cmdnode node, char *env[])
{
	debug("-- begin execution --\n");
	if (check_builtin(node) >= 0)
		exec_builtin(node, env);
	else
	{
		debug_str("executing", node.cmd);
		child_executes(node, env);
	}
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

	debug("-- solve path --");
	debug_str("cmd 1 BEFORE", (*node).cmd);
	if (!node->cmd)
		return (0);
	if (node->cmd[0] == '/')
		return (1);
	else
	{
		if (check_builtin(*node) >= 0)
		{
			debug_str("cmd 1 AFTER BUILTIN", (*node).cmd);
			return (1);
		}
		cmd_path = find_path(node->cmd, env);
		if (!cmd_path)
		{
			my_perror("command path not found 🌸");
			return (0);
		}
		debug_str("cmd", node->cmd);
		debug_str("before: aarg0", node->argv[0]);
		free(node->cmd); //
		node->cmd = cmd_path;
		//node->argv[0] = node->cmd;
		debug_str("cmd 1 AFTER", (*node).cmd);
		debug_str("after: arg0", node->argv[0]);
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


void	my_pipex(int n_nodes, t_cmdnode nodes[], char *env[])
{
	int	i;
	int	default_in;
	int	default_out;
	// int fd[2];

	default_in = dup(STDIN_FILENO);
	default_out = dup(STDOUT_FILENO);
	i = 0;
	while (i < n_nodes) // node1 | nodeUlt
	{
		
		
		debug_int("new node-------------------", i);
		if (i == n_nodes - 1)
			nodes[i].last_node = 1;
		
		if (solve_path(&(nodes[i]), env))
			my_exec(nodes[i], env);

		
		i++;
	}
	dup2(default_in, STDIN_FILENO);
	dup2(default_out, STDOUT_FILENO);
	debug("exit pipex\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:43:14 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 20:10:29 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * substitute line with its expanded version.
 * It also saves a '\n' at the end
 * line "hola $USER at $HOME"
 * new_line "hola username ar home/username"
 */
void	expand_heredoc(char **line, t_shcontext *env)
{
	int		i;
	char	*new_line;
	char	*dollar_exp;
	int		j;

	new_line = my_calloc(ft_strlen(*line) + 1, 1);
	i = 0;
	j = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			j += expand_dollar_simplehd(*line, &i, &dollar_exp);
			j += expand_dollar(*line, &i, &dollar_exp, env);
			new_line = ft_strjoin_inplace(&new_line, dollar_exp);
			free(dollar_exp);
		}
		else
		{
			new_line = ft_strappendc_inplace(new_line, (*line)[i++]);
			j++;
		}
	}
	new_line = ft_strappendc_inplace(new_line, '\n');
	free(*line);
	*line = new_line;
}

void	here_doc_child(char *del, int pipe_fd[2], t_shcontext *env)
{
	char	*line;

	signal_heredoc();
	close(pipe_fd[0]);
	while (1)
	{
		line = readline(ANSI_COLOR_GREEN "> " ANSI_COLOR_RESET);
		if (!line)
			my_perr_arg_exit(
				"warning: heredoc delimited by EOF. Wanted", del);
		if (ft_strncmp(line, del, 2) == 0)
			exit(0);
		expand_heredoc(&line, env);
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

/**
 * HEREDOC process
 * It uses a pipe.
 * @arg del: delimiter
 * @arg env: context variable
 */
int	here_doc(char *del, t_shcontext *env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		here_doc_child(del, pipe_fd, env);
		return (0);
	}
	else
	{
		signal_ignore();
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		env->status = status % 255;
		if (env->status == 130)
			return (-1);
		return (pipe_fd[0]);
	}
}

int	process_heredocs(int n_nodes, t_cmdnode *nodes, t_shcontext *env)
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
					= here_doc(nodes[i].redir.infiles[j].filename_delim, env);
				if (env->status == 130)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * 
	if (WIFEXITED(status)) // child terminated normally?
		-> WEXITSTATUS(status) // returns the exit status of the child.
	else if (WIFSIGNALED(status)) // child terminated w signal not handled
		-> 128 + WTERMSIG(status) //  signal that terminated the child process
	else 
		-> status // the same

 */
int	get_real_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (status);
}

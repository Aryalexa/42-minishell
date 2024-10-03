/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:43:14 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 16:06:29 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_line(char **line)
{
	char	*buffer;
	int		i;
	int		n_read;
	char	c;

	buffer = (char *)my_calloc(10000, 1);
	write(1, "> ", 2);
	i = 0;
	n_read = 0;
	n_read = read(0, &c, 1);
	if (c == '\0')
		return (0);
	while (c != '\n')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		n_read = read(0, &c, 1);
		if (n_read == 0)
			c = '\0';
	}
	buffer[i] = '\0';
	*line = buffer;
	return (n_read);
}

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

int	here_doc(char *delimiter, t_shcontext *env)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;
	int		status;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		signal_heredoc();
		debug("1 🌵HD child - signal_heredoc");
		close(pipe_fd[0]);
		while (read_line(&line))
		{
			if (ft_strncmp(line, delimiter, 2) == 0)
				exit(0);
			expand_heredoc(&line, env);
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		// if (!line[0])
		// 	ft_putstr_fd("🔴EOFFFFF", 2); // 
		my_perror_arg("\nwarning: heredoc delimited by EOF. Wanted", delimiter);
		exit(0);
	}
	else
	{
		signal_ignore();
		debug("🌵HD parent - signal_ignore"); //
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (status == 33280) // Si el hijo terminó por señal -> 33280 % 250 == 130
		{
			env->status = 130;
			return (-1);
		}
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
	if (WIFEXITED(status)) // returns true if the child terminated normally
	-> // returns the exit status of the child.
	else if (WIFSIGNALED(status)) // child terminated, bc signal not handled
	-> //  signal that terminated the child process
	else if WIFSTOPPED(status) returns nonzero value if child process is stopped
	->  //  signal that caused the child process to stop
	else
	-> status

 */
int	get_signal_status(int status)
{
	if (WIFEXITED(status))
	{
		debug_int("child terminated . WEXITSTATUS(status)", WEXITSTATUS(status)); //
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		debug_int("child singnal not-h term. status:", 128 + WTERMSIG(status)); //
		return (128 + WTERMSIG(status));
	}
	else
	{
		debug_int("else. status:", status); //
		return (status);
	}
}

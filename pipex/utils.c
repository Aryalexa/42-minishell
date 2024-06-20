/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:09 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/21 00:23:09 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	my_exit(char *msg)
{
	perror(msg);
	exit(1);
}

char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*path_i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_i = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path_i, cmd);
		free(path_i);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	ft_free_arrstr(paths);
	return (NULL);
}

// void	printerr_cur_cmd(char *cmd)
// {
// 	write(2, "while executing ", 16);
// 	write(2, cmd, ft_strlen(cmd));
// 	write(2, "...\n", 4);
// }

void	close_and_dup(int pipefd[], int is_child)
{
	if (is_child == 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}


int	read_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	write(1, "> ", 2);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

int	here_doc(char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		exit(1); // TODO
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (read_line(&line))
		{
			// write(2, line, ft_strlen(line));
			// write(1, "]", 1);
			line[ft_strlen(line) - 1] = '\0';
			if (ft_strcmp(line, delimiter) == 0)
				exit(0);
			line[ft_strlen(line)] = '\n';
			write(pipe_fd[1], line, ft_strlen(line));
		}
		return (0);
	}
	else
	{
		close(pipe_fd[1]);
		//dup2(pipe_fd[0], STDIN_FILENO);
		wait(NULL);
		return (pipe_fd[0]);
	}
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:09 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/12 21:37:10 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
//#include <sys/types.h>
#include "../../libft/libft.h"
#include "../pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

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

void	printerr_cur_cmd(char *cmd)
{
	write(2, "while executing ", 16);
	write(2, cmd, ft_strlen(cmd));
	write(2, "...\n", 4);
}

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

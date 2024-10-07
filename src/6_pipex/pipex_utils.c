/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:09 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 19:18:09 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @return complete path or NULL if not found in PATH
 */
char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		ft_strjoin_inplace(&paths[i], "/");
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_arrstr(paths), cmd_path);
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

/**
 * changes the node cmd to its full path.
 * supported:
 * - relative and absolute routes (abs routes start w /)
 * - if relative: check if built-in or not
 * 
 * @return bool: 1 when resolved, 0 if error
 */
int	solve_path(t_cmdnode *node, char *env[], int *status)
{
	char		*cmd_path;

	if (!node->cmd)
		return (1);
	if (node->cmd[0] == '/')
		return (1);
	else
	{
		if (check_builtin(*node) >= 0)
			return (1);
		cmd_path = find_path(node->cmd, env);
		if (!cmd_path)
		{
			my_perr_arg("command not found 🌸", node->cmd);
			*status = 127;
			return (0);
		}
		free(node->cmd);
		node->cmd = cmd_path;
		return (1);
	}
}

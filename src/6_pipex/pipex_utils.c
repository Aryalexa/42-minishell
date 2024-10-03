/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:09 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 16:04:58 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
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

int	expand_dollar_simplehd(char *code, int *i, char **val)
{
	if (!code[*i + 1] || !ft_isalnum(code[*i + 1]))
	{
		*val = ft_strdup("$");
		return (1);
	}
	return (0);
}

/**
 * changes the node cmd to its full path.
 * return bool: 1 when resolved, 0 if error
 * supported:
 * - ruta relativa o absoluta (empieza con /)
 * - si es relativo: si es comando built-in o no
 * 
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
			my_perror_arg("command not found 🌸", node->cmd);
			*status = 127;
			return (0);
		}
		free(node->cmd);
		node->cmd = cmd_path;
		return (1);
	}
}

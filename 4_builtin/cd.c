/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/13 18:07:47 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * get abs path
 */
int	checkpath(char	*path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

/**
 * create or replace env var in env
 */
void	update_pwd(char *key, char *value, char *env[])
{
	int		i;
	char	*line;

	i = 0;
	while (env[i] && ft_strnstr(env[i], key, ft_strlen(key)) == NULL)
		i++;
	line = ft_strjoin(key, value);
	free(env[i]);
	env[i] = line;
}

/**
 * Change directory.
 * it calls chdir and change the env var PWD
 */
void	exec_cd(t_cmdnode node, t_env env)
{
	char	cwd[PATH_MAX];

	if (node.argc == 1)
		return ;
	if (node.argc > 2)
	{
		my_perror("Error. Too many arguments.");
		return ;
	}
	if (!checkpath(node.argv[1]))
	{
		my_perror("Error. No such file or directory.");
		return ;
	}
	if (chdir(node.argv[1]) != 0)
	{
		my_perror("Error. Failed to change directory.");
		return ;
	}
	getcwd(cwd, PATH_MAX);
	update_pwd("PWD=", cwd, env.env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 13:27:12 by msoriano         ###   ########.fr       */
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

char	*get_path(char *key, t_shcontext *env)
{
	int		i;
	char	*k;
	char	*val;

	i = envvar_index(key, env);
	if (i == -1)
		return (NULL);
	get_kv(env->env[i], &k, &val);
	free(k);
	return (val);
}

/**
 * Change directory.
 * it calls chdir and change the env var PWD
 * 
 * 
 */
int	exec_cd(t_cmdnode node, t_shcontext *env)
{
	char	cwd[PATH_MAX];
	char	*new;

	if (node.argc > 2)
	{
		my_perror("Error. Too many arguments.");
		return (1);
	}
	if (node.argc == 1)
		new = get_path("HOME", env);
	else if (!checkpath(node.argv[1]))
	{
		my_perror("Error. No such file or directory.");
		return (1);
	}
	else
		new = node.argv[1];
	if (chdir(new) != 0)
	{
		my_perror("Error. Failed to change directory.");
		return (1);
	}
	getcwd(cwd, PATH_MAX);
	update_envvar("PWD", cwd, env);
	return (0);
}

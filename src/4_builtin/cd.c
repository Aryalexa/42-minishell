/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 14:41:23 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * check if path exists and we can access
 */
int	checkpath(char	*path)
{
	return (access(path, F_OK) == 0);
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
 * update cd env variables: PWD and OLDPWD
 * - it distinguishes the case when doing "cd .." and parent does not exist.
 */
int	update_envvar_cd(t_shcontext *env)
{
	char	*cwd;
	char	*oldcwd;

	oldcwd = get_env_var("PWD", env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		my_perror("cd: error retrieving current directory: getcwd");
		update_envvar("OLDPWD", oldcwd, env);
		update_envvar("PWD", ft_strjoin_inplace(&oldcwd, "/.."), env);
	}
	else
	{
		update_envvar("PWD", cwd, env);
		update_envvar("OLDPWD", oldcwd, env);
		free(cwd);
	}
	free(oldcwd);
	return (0);
}

/**
 * Change directory.
 * it calls chdir and updates the env vars PWD and OLDPWD
 * 
 */
int	exec_cd(t_cmdnode node, t_shcontext *env)
{
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
	return (update_envvar_cd(env));
}

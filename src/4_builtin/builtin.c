/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/05 19:11:54 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	envvar_index(char *key_srch, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	int		cmp;

	i = 0;
	while (env->env[i])
	{
		get_kv(env->env[i], &key, &value);
		cmp = ft_strcmp(key_srch, key);
		free(key);
		free(value);
		if (cmp == 0)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * replace env var in env
 */
void	update_envvar(char *key, char *value, t_env *env)
{
	int		i;
	char	*line;
	char	*aux;

	i = envvar_index(key, env);
	if (i == -1)
		return ;
	aux = ft_strjoin(key, "=");
	line = ft_strjoin(aux, value);
	free(aux);
	free(env->env[i]);
	env->env[i] = line;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 19:39:51 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_del_one(t_shcontext *env, char *var)
{
	char	**copy;
	int		i;
	int		j;
	char	*key;
	char	*value;

	copy = my_calloc(env->n_env - 1, sizeof(char *));
	i = 0;
	j = 0;
	while (env->env[i])
	{
		get_kv(env->env[i], &key, &value);
		if (ft_strcmp(key, var) != 0)
			copy[j++] = ft_strdup(env->env[i]);
		free(key);
		free(value);
		i++;
	}
	copy[j] = NULL;
	ft_free_arrstr(env->env);
	env->env = copy;
	env->n_env--;
}

int	exec_unset(t_cmdnode node, t_shcontext *env)
{
	int	i;

	i = 1;
	while (i < node.argc)
	{
		if (envvar_index(node.argv[i], env) != -1)
			env_del_one(env, node.argv[i]);
		i++;
	}
	return (0);
}

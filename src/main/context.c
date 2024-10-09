/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:09:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 14:38:33 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * after dup, this function will read env til it finds "SHLVL"
 * if it doesnt find any occurrences it will create SHLVL = 0
 * if it does, shlvl + 1
 */
static void	update_shlvl(t_shcontext *env)
{
	int		i;
	char	*lvl;

	i = 0;
	while (env->env[i] && ft_strnstr(env->env[i], "SHLVL", 5) == NULL)
		i++;
	if (!env->env[i])
	{
		env_add_one(env, "SHLVL");
		update_envvar("SHLVL", "1", env);
	}
	else
	{
		lvl = ft_itoa(ft_atoi(&env->env[i][6]) + 1);
		update_envvar("SHLVL", lvl, env);
		free(lvl);
	}
}

/**
 * This creates a copy and returns the env and the number of items.
 * - the original env that main receives has a null terminator
 * - the copy too.
 */
static char	**dup_env(char *env_src[], int *save_size)
{
	char	**env;
	int		size;
	int		i_src;

	i_src = 0;
	while (env_src[i_src] != NULL)
		i_src++;
	env = my_malloc((i_src + 1) * sizeof(char *));
	size = 0;
	i_src = 0;
	while (env_src[i_src] != NULL)
	{
		if (ft_strchr(env_src[i_src], '='))
		{
			env[size++] = ft_strdup(env_src[i_src]);
			if (env[size - 1] == NULL)
				return (NULL);
		}
		i_src++;
	}
	env[size] = NULL;
	*save_size = size + 1;
	return (env);
}

t_shcontext	create_context(char *envp[])
{
	t_shcontext	env;

	env.o_env = envp;
	env.env = dup_env(envp, &env.n_env);
	update_shlvl(&env);
	env.status = 0;
	env.open_quote = '\0';
	env.nopipe = 0;
	return (env);
}

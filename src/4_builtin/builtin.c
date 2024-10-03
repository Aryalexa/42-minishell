/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 13:29:12 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	envvar_index(char *key_srch, t_shcontext *env)
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
void	update_envvar(char *key, char *value, t_shcontext *env)
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

void	print_export_style(char *line)
{
	int	i;

	ft_printf("declare -x ");
	i = ft_strchri(line, '=');
	if (i == -1)
		ft_printf("%s\n", line);
	else
	{
		write(1, line, i + 1);
		ft_printf("\"%s\"\n", line + i + 1);
	}
}

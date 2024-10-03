/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 18:09:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_add_one(t_shcontext *env, char *var)
{
	char	**copy;
	int		i;

	copy = my_calloc((env->n_env + 1), sizeof(char *));
	i = 0;
	while (env->env[i])
	{
		copy[i] = ft_strdup(env->env[i]);
		i++;
	}
	copy[i++] = ft_strdup(var);
	copy[i] = NULL;
	ft_free_arrstr(env->env);
	env->env = copy;
	env->n_env++;
}

/**
 * "key=value" -> key, value
 */
void	get_kv(char *line, char **key, char **value)
{
	int	i;

	i = ft_strchri(line, '=');
	if (i == -1)
		i = ft_strlen(line);
	*key = my_calloc(i + 1, 1);
	ft_strlcpy(*key, line, i + 1);
	if (i == (int) ft_strlen(line))
		*value = my_calloc(1, 1);
	else
	{
		*value = my_calloc(ft_strlen(line) - i, 1);
		ft_strlcpy(*value, line + i + 1, ft_strlen(line) - i);
	}
}

void	process_assignment(char *statement, t_shcontext *env)
{
	char	*key;
	char	*value;

	get_kv(statement, &key, &value);
	if (envvar_index(key, env) != -1)
		update_envvar(key, value, env);
	else
		env_add_one(env, statement);
	free(key);
	free(value);
}

int	export_vars(t_cmdnode node, t_shcontext *env)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	while (i < node.argc)
	{
		if (node.argv[i][0] == '='
			|| ft_isdigit(node.argv[i][0]) || ft_strchr(node.argv[i], '-'))
		{
			my_perr_arg("error. Not a valid identifier", node.argv[i]);
			status = 1;
		}
		else
		{
			if (ft_strchri(node.argv[i], '=') != -1)
				process_assignment(node.argv[i], env);
			else if (envvar_index(node.argv[i], env) == -1)
				env_add_one(env, node.argv[i]);
		}
		i++;
	}
	return (status);
}

// si no hay igual > key = line
// 		si key existe -> nada
// 		else crear
// si hay =, separar -> key, val = sep(line)
// 		si key existe -> sust
// 		else crear
int	exec_export(t_cmdnode node, t_shcontext *env)
{
	int		i;

	if (node.argc == 1)
	{
		i = 0;
		while (env->env[i])
			print_export_style(env->env[i++]);
		return (0);
	}
	else
		return (export_vars(node, env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/13 20:44:08 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

char **add_one(char **list, int *n_items, char *new_str)
{
	char	**copy;
	int		i;

	copy = malloc((*n_items + 1) * sizeof(char *));
	i = 0;
	while (i < *n_items - 1)
	{
		copy[i] = list[i];
		i++;
	}
	copy[i++] = ft_strdup(new_str);
	copy[i] = NULL;
	free(list);
	(*n_items)++;
	return (copy);
}

void	get_kv(char *line, char **key, char **value)
{
	int	i;

	i = ft_strchri(line, '=');
	*key = my_calloc(i + 1, 1);
	*value = my_calloc(ft_strlen(line) - i, 1);
	ft_strlcpy(*key, line, i + 1);
	ft_strlcpy(*value, line + i + 1, ft_strlen(line) - i);
}

void	process_assignment(char *statement, t_env *env)
{
	char	*key;
	char	*value;

	get_kv(statement, &key, &value);
	debug_str("key", key);
	debug_str("value", value);
	if (envvar_index(key, env->env) != -1)
		update_envvar(key, value, (*env).env);
	else
		(*env).env = add_one(env->env, &(env->n_env), statement);
	free(key);
	free(value);
}

// si no hay igual > key = line
// 		si key existe -> nada
// 		else crear
// si hay =, separar -> key, val = sep(line)
// 		si key existe -> sust
// 		else crear
void	exec_export(t_cmdnode node, t_env *env)
{
	int		i;

	if (node.argc == 1)
	{
		i = 0;
		while (env->env[i])
			print_export_style(env->env[i++]);
	}
	else
	{
		i = 1;
		while (i < node.argc)
		{
			if (ft_strchri(node.argv[i], '=') == -1)
			{
				if (envvar_index(node.argv[i], env->env) == -1)
					(*env).env = add_one(env->env, &(env->n_env), node.argv[i]);
			}
			else
				process_assignment(node.argv[i], env);
			i++;
		}
	}
}

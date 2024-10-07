/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 17:11:18 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_var(char *var_key, t_shcontext *env)
{
	char	*var_value;
	char	*aux;
	int		j;

	var_value = NULL;
	j = envvar_index(var_key, env);
	if (j == -1)
		return ((char *) my_calloc(1, 1));
	get_kv(env->env[j], &aux, &var_value);
	free(aux);
	return (var_value);
}

/**
 * get envvar name.
 * it duplicates the name from the text and returns it,
 * it copies everything after the $ while is alphanum. 
 */
char	*get_varname(char *text, int *i)
{
	char	*name;
	int		j;

	name = my_calloc(ft_strlen(text) + 1, 1);
	(*i)++;
	j = 0;
	while (text[*i] && ft_isalnum(text[*i]))
		name[j++] = text[(*i)++];
	return (name);
}

/**
 * A $ have been encountered so we try to expand the env var.
 * It starts with text[i] == '$'
 * @arg text	str to parse
 * @arg i		text index
 * @arg env		context var
 * @return		str with the value of the envvar
 */
char	*expand_dollar(char *text, int *i, t_shcontext *env)
{
	char	*varname;
	char	*val;

	if (!text[*i + 1] || isreservedall(text[*i + 1]) || is_space(text[*i + 1]))
	{
		(*i)++;
		if (isquote(text[*i + 1]) && text[*i + 1] != env->open_quote)
			val = ft_strdup("");
		else
			val = ft_strdup("$");
		return (val);
	}
	else if (text[*i + 1] == '?')
	{
		(*i) += 2;
		val = ft_itoa(env->status);
	}
	else
	{
		varname = get_varname(text, i);
		val = get_env_var(varname, env);
		free(varname);
	}
	return (val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 20:25:48 by macastro         ###   ########.fr       */
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
 * if quotes are open, q_char is " OR ' , otherwise NULL
 * - input= $<quote> - we came from open quotes
 * - input = $<quote> - new open quotes
 * - input = $\0 OR $<reserved> OR $<space>
 * 
 */
int	expand_dollar_simple(char *text, int *i, char **val, char q_char)
{
	if (!text[*i + 1] || is_reserved_all(text[*i + 1])
		|| ft_isspace(text[*i + 1]))
	{
		if (text[*i + 1] == q_char)
			*val = ft_strdup("$");
		else if (is_quote(text[*i + 1]))
			*val = ft_strdup("");
		else
			*val = ft_strdup("$");
		return (1);
	}
	return (0);
}

/**
 * expands text and saves it in val
 * returns the lenght of val
 */
int	expand_dollar(char *text, int *i, char **val, t_shcontext *env)
{
	char	*var;
	int		j;

	var = my_calloc(ft_strlen(text) + 1, 1);
	j = 0;
	if (!text[*i + 1] || is_reserved_all(text[*i + 1])
		|| ft_isspace(text[*i + 1]))
	{
		(*i)++;
		free(var);
		return (0);
	}
	else if (text[*i + 1] == '?')
	{
		(*i) += 2;
		*val = ft_itoa(env->status);
		free(var);
		return (ft_strlen(*val));
	}
	(*i)++;
	while (text[*i] && ft_isalnum(text[*i]))
		var[j++] = text[(*i)++];
	*val = get_env_var(var, env);
	free(var);
	return (ft_strlen(*val));
}

int	expand_quotes(char *text, int *i, char	**val, t_shcontext *env)
{
	int		j;
	char	*dollar_val;
	char	q_char;

	j = 0;
	q_char = text[*i];
	(*i)++;
	dollar_val = NULL;
	*val = my_calloc(ft_strchri(&text[*i], q_char) + 1, 1);
	while (text[*i] != q_char)
	{
		if (q_char == '"' && text[*i] == '$')
		{
			j += expand_dollar_simple(text, i, &dollar_val, q_char);
			j += expand_dollar(text, i, &dollar_val, env);
			*val = ft_strjoin_inplace(val, dollar_val);
			free(dollar_val);
		}
		else
		{
			*val = ft_strappendc_inplace(*val, text[(*i)++]);
			j++;
		}
	}
	(*val)[j] = '\0';
	(*i)++;
	return (ft_strlen(*val));
}

/**
 * Expand text.
 * read the text text and returns the expanded version
 * cases:
 * - " -> interprete
 * - $
 * - no nulo
 */
char	*expand_text(char *text, t_shcontext *env)
{
	int		i;
	char	*val;
	char	*aux_val;
	int		j;

	val = my_calloc(ft_strlen(text) + 1, 1);
	i = 0;
	j = 0;
	while (text[i])
	{
		if (is_quote((text)[i]))
		{
			j += expand_quotes(text, &i, &aux_val, env);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else if ((text)[i] == '$')
		{
			j += expand_dollar_simple(text, &i, &aux_val, '\0');
			j += expand_dollar(text, &i, &aux_val, env);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else
		{
			val = ft_strappendc_inplace(val, text[i++]);
			j++;
		}
	}
	return (val);
}

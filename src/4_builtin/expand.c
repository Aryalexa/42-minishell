/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 13:30:49 by msoriano         ###   ########.fr       */
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
int	expand_dollar_simple(char *code, int *i, char **val, char q_char)
{
	if (!code[*i + 1] || is_reserved_all(code[*i + 1])
		|| ft_isspace(code[*i + 1]))
	{
		debug_str("input:", &code[*i]);
		if (code[*i + 1] == q_char)
			*val = ft_strdup("$");
		else if (is_quote(code[*i + 1]))
			*val = ft_strdup("");
		else
		{
			debug("qchar entro!");
			*val = ft_strdup("$");
		}
		return (1);
	}
	return (0);
}

/**
 * expands code and saves it in val
 * returns the lenght of val
 */
int	expand_dollar(char *code, int *i, char **val, t_shcontext *env)
{
	char	*var;
	int		j;

	var = my_calloc(ft_strlen(code) + 1, 1);
	j = 0;
	if (!code[*i + 1] || is_reserved_all(code[*i + 1])
		|| ft_isspace(code[*i + 1]))
	{
		(*i)++;
		free(var);
		return (0);
	}
	else if (code[*i + 1] == '?')
	{
		(*i) += 2;
		*val = ft_itoa(env->status);
		free(var);
		return (ft_strlen(*val));
	}
	(*i)++;
	while (code[*i] && ft_isalnum(code[*i]))
		var[j++] = code[(*i)++];
	*val = get_env_var(var, env);
	free(var);
	return (ft_strlen(*val));
}

int	expand_quotes(char *code, int *i, char	**val, t_shcontext *env)
{
	int		j;
	char	*dollar_val;
	char	q_char;

	j = 0;
	q_char = code[*i];
	(*i)++;
	dollar_val = NULL;
	*val = my_calloc(ft_strchri(&code[*i], q_char) + 1, 1);
	while (code[*i] != q_char)
	{
		if (q_char == '"' && code[*i] == '$')
		{
			j += expand_dollar_simple(code, i, &dollar_val, q_char);
			j += expand_dollar(code, i, &dollar_val, env);
			*val = ft_strjoin_inplace(val, dollar_val);
			free(dollar_val);
		}
		else
		{
			*val = ft_strappendc_inplace(*val, code[(*i)++]);
			j++;
		}
	}
	(*val)[j] = '\0';
	(*i)++;
	return (ft_strlen(*val));
}

/**
 * read the code and returns the expanded version
 * cases:
 * - " -> interprete
 * - $
 * - no nulo
 */
char	*expand_token_val(char *code, t_shcontext *env)
{
	int		i;
	char	*val;
	char	*aux_val;
	int		j;

	i = 0;
	val = my_calloc(ft_strlen(code) + 1, 1);
	j = 0;
	while (code[i])
	{
		if (is_quote((code)[i]))
		{
			j += expand_quotes(code, &i, &aux_val, env);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else if ((code)[i] == '$')
		{
			j += expand_dollar_simple(code, &i, &aux_val, '\0');
			j += expand_dollar(code, &i, &aux_val, env);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else
		{
			val = ft_strappendc_inplace(val, code[i++]);
			j++;
		}
	}
	return (val);
}

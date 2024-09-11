/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/11 14:01:10 by macastro         ###   ########.fr       */
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
 */
int	expand_dollar_simple(char *code, int *i, char **val, char q_char)
{
	//ft_printf("---🍇in:expand_dollar code:%s\n", code);
	if (!code[*i + 1] || is_reserved_all(code[*i + 1]))
	{
		if (code[*i + 1] == q_char)
			*val = ft_strdup("$");
		//ft_printf("----just one dollar!\n");
		else if (is_quote(code[*i + 1]))
			*val = ft_strdup("");
		else
			*val = ft_strdup("$");
		//ft_printf("---🍇out:expand_dollar\n");
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
	if (!code[*i + 1] || is_reserved_all(code[*i + 1]))
	{
		(*i)++;
		free(var);
		return (0);
	}
	else if (code[*i + 1] == '?')
	{
		(*i) += 2;
		*val = ft_itoa(env->status);
		return (ft_strlen(*val));
	}
	(*i)++;
	while (code[*i] && !is_reserved_all(code[*i]) && !ft_isspace(code[*i]))
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
	//ft_printf("---🍏in: expand_quotes\n"); //
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
	//ft_printf("---🍏out: expand_quotes, val:%s\n", *val); //
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

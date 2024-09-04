/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/21 13:53:02 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
/**
 * if quotes are open, q_char is " OR ' , otherwise NULL
 */
int	expand_dollar(char *code, int *i, char **val, char q_char)
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
		(*i)++;
		//ft_printf("---🍇out:expand_dollar\n");
		return (1);
	}
	// USAR ENV
	(*i)++;
	while (code[*i] && !is_reserved_all(code[*i]) && !ft_isspace(code[*i]))
	{
		//ft_printf("--expand_dollar--i:%i code[i]:%c\n", *i, code[*i]);
		(*i)++;
	}
	*val = ft_strdup("DOLLAR"); //
	//ft_printf("---🍇out:expand_dollar val:%s\n", *val);
	return (ft_strlen(*val));
}

int	expand_quotes(char *code, int *i, char	**val)
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
			j += expand_dollar(code, i, &dollar_val, q_char);
			*val = ft_strjoin_inplace(val, dollar_val);
			free(dollar_val);
		}
		else
			(*val)[j++] = code[(*i)++];
	}
	(*val)[j] = '\0';
	(*i)++;
	//ft_printf("---🍏out: expand_quotes, val:%s\n", *val); //
	return (ft_strlen(*val));
}

/**
 * modify the code to its expansion
 * cases:
 * - " -> interprete
 * - $
 * - no nulo
 */
char	*expand_token_val(char *code)
{
	int		i;
	char	*val;
	char	*aux_val;
	int		j;

	i = 0;
	val = my_calloc(ft_strlen(code) + 1, 1);
	j = 0;
	while ((code)[i])
	{
		if (is_quote((code)[i]))
		{
			j += expand_quotes(code, &i, &aux_val);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else if ((code)[i] == '$')
		{
			j += expand_dollar(code, &i, &aux_val, '\0');
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else
			val[j++] = (code)[i++];
	}
	val[j] = '\0';
	return (val);
}

int	envvar_index(char *key, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], key, ft_strlen(key)) == NULL)
		i++;
	if (!env[i])
		return (-1);
	return (i);
}


/**
 * create or replace env var in env
 */
void	update_envvar(char *key, char *value, char *env[]) // funciona????
{
	int		i;
	char	*line;
	char	*aux;

	i = envvar_index(key, env);
	if (i == -1)
		return ;
	aux = ft_strjoin(key, "=");
	line = ft_strjoin(aux, value);
	free(env[i]);
	free(aux);
	env[i] = line;
}

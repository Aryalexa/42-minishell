/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/13 16:11:52 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	expand_dollar(char *code, int *i, char **val)
{
	//ft_printf("---🍇in:expand_dollar code:%s\n", code);
	if (!code[*i + 1] || is_reserved_all(code[*i + 1]))
	{
		//ft_printf("----just one dollar!\n");
		if (is_quote(code[*i + 1]))
			*val = ft_strdup("");
		else
			*val = ft_strdup("$");
		(*i)++;
		//ft_printf("---🍇out:expand_dollar\n");
		return (1);
	}
	// USAR ENV
	(*i)++;
	while (code[*i] && !is_reserved_all(code[*i]))
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
			j += expand_dollar(code, i, &dollar_val);
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
			j += expand_dollar(code, &i, &aux_val);
			val = ft_strjoin_inplace(&val, aux_val);
			free(aux_val);
		}
		else
			val[j++] = (code)[i++];
	}
	val[j] = '\0';
	//swap_and_free_strings(code, &val);
	return (val);
}

char	*get_pwd(char *env[])
{
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PWD", 3) == NULL)
		i++;
	return (&env[i][4]);
}

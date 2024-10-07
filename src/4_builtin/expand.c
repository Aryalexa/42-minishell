/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 17:12:09 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * "..." and '...' expander
 * it saves the open quote char that is used inside expand_dollar
 * - (") expands env vars
 * - (') does not expand, the content is treated a plain string
 * 
 */
char	*expand_quotes(char *text, int *i, t_shcontext *env)
{
	char	*val;
	char	q_char;
	char	*aux_val;

	q_char = text[*i];
	env->open_quote = q_char;
	(*i)++;
	val = my_calloc(ft_strchri(&text[*i], q_char) + 1, 1);
	while (text[*i] != q_char)
	{
		if (q_char == '"' && text[*i] == '$')
		{
			aux_val = expand_dollar(text, i, env);
			val = ft_strjoin_inplace2(&val, &aux_val);
		}
		else
			val = ft_strappendc_inplace(val, text[(*i)++]);
	}
	(*i)++;
	env->open_quote = '\0';
	return (val);
}

/**
 * Expand text.
 * read the text and returns the expanded version
 * cases:
 * - " -> expand quote
 * - $ -> expand dollar
 * - otherwise -> no expand
 */
char	*expand_text(char *text, t_shcontext *env)
{
	int		i;
	char	*val;
	char	*aux_val;

	val = my_calloc(ft_strlen(text) + 1, 1);
	i = 0;
	while (text[i])
	{
		if (isquote(text[i]))
		{
			aux_val = expand_quotes(text, &i, env);
			val = ft_strjoin_inplace2(&val, &aux_val);
		}
		else if ((text)[i] == '$')
		{
			aux_val = expand_dollar(text, &i, env);
			val = ft_strjoin_inplace2(&val, &aux_val);
		}
		else
			val = ft_strappendc_inplace(val, text[i++]);
	}
	return (val);
}

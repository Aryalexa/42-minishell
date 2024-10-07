/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:56:54 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 15:55:56 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * tokenize $
 * 
 */
static int	lexer_aux_dollar(const char *input, t_token *tokens,
	int *_i, int idx)
{
	int	i;

	i = *_i;
	if (input[i] == '$')
	{
		tokens[idx].type = TKN_ENVAR;
		tokens[idx].val = read_word(input, &i);
	}
	if (tokens[idx].val == NULL)
		return (-1);
	idx++;
	*_i = i;
	return (idx);
}

/**
 * tokenize < << > >>
 */
static int	lexer_aux_iof(const char *input, t_token *tokens, int *_i, int idx)
{
	int	i;

	i = *_i;
	if (input[i] == '<')
	{
		if (input[++i] == '<')
		{
			tokens[idx].type = TKN_HRDC;
			i++;
		}
		else
			tokens[idx].type = TKN_LT;
	}
	else if (input[i] == '>')
	{
		if (input[++i] == '>')
		{
			tokens[idx].type = TKN_APPD;
			i++;
		}
		else
			tokens[idx].type = TKN_GT;
	}
	*_i = i;
	return (++idx);
}

static int	update_token(t_token *tokens, int t_i,
	t_tokenType type, char *value)
{
	if (!value)
		return (-1);
	tokens[t_i].type = type;
	tokens[t_i].val = value;
	return (t_i + 1);
}

/**
 * LEXER
 * It reads the input and creates an array of tokens.
 * It just classifies what it encounters in the input.
 * It identifies some syntax errors.
 * @return number of created tokens, -1 if error.
 */
int	lexer(const char *input, t_token *tokens)
{
	int	i;
	int	t_i;

	ft_memset(tokens, '\0', sizeof(t_token) * MAX_TKNS);
	i = 0;
	t_i = 0;
	while (input[i] && t_i != -1)
	{
		while (is_space(input[i]))
			i++;
		if (input[i] == '$')
			t_i = lexer_aux_dollar(input, tokens, &i, t_i);
		else if (input[i] == '|')
		{
			tokens[t_i++].type = TKN_PIPE;
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			t_i = lexer_aux_iof(input, tokens, &i, t_i);
		else if (input[i])
			t_i = update_token(tokens, t_i, TKN_WORD, read_word(input, &i));
		if (t_i >= MAX_TKNS)
			return (my_perror("error: too many tokens!"), -1);
	}
	return (t_i);
}

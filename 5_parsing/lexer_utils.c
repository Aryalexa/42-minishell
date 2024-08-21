/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:57:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/21 13:29:52 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * check quotes and return found word.
 * returns string (with quotes if there were any)
 * 
 */
char	*read_word(const char *input, int *i)
{
	char	*word;
	int		j;
	char	q_char;

	q_char = '\0';
	j = *i;
	while (input[j]
		&& ((!q_char && !(is_reserved(input[j]) || ft_isspace(input[j])))
			|| q_char))
	{
		if (!q_char && (input[j] == '"' || input[j] == '\''))
			q_char = input[j];
		else if (q_char && input[j] == q_char)
			q_char = '\0';
		j++;
	}
	if (q_char)
	{
		my_perror("syntax error: quote not finished.");
		return (*i = j, NULL);
	}
	word = ft_strndup(&input[*i], j - *i);
	if (!word)
		my_perror_exit("strndup: mem error.");
	return (*i = j, word);
}

void	free_tokens(t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		if(tokens[i].type == TKN_ENVAR ||tokens[i].type == TKN_WORD)
			free(tokens[i].val);
		i++;
	}
}

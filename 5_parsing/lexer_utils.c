/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:57:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 12:24:45 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * return the word without wrapping quotes
 */
char	*read_quote(const char *input, int *i)
{
	char	*word;
	char	q;
	int		final;

	q = input[*i];
	final = (*i) + 1 ;
	while (input[final] && input[final] != q)
		final++;
	if (input[final] == q)
	{
		word = ft_strndup(&input[*i], final - *i + 1);
		*i = final + 1;
		if (!word)
			my_perror_exit("strndup: mem error.");
		return (word);
	}
	my_perror("syntax error: quote not finished.");
	return (NULL);
}

// char	*dup_clean_simplequotes(const char *str, int len)
// {
// 	char	*res;
// 	int		i;
// 	int		j;

// 	if (ft_strchri(str, '\'') < len && ft_strchri(str, '\'') != -1)
// 	{
// 		if (len < 0)
// 			my_perror_exit("fatal error 345.");
// 		res = (char *)malloc(sizeof(char) * (len - 1));
// 		if (!res)
// 			my_perror_exit("malloc: mem error.");
// 		i = 0;
// 		j = 0;
// 		while (str[i] && i < len)
// 		{
// 			if (str[i] != '\'')
// 				res[j++] = str[i++];
// 			else
// 				i++;
// 		}
// 		res[j] = '\0';
// 		return (res);
// 	}
// 	else
// 		return (ft_strndup(str, len));
// }

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

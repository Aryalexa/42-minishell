

#include "parsing.h"

/**
 * return the word without wrapping quotes
 */
char	*read_quote(const char *input, int *i)
{
	char	*word;
	char	q;
	int		j;

	q = input[*i];
	j = *i + 1;
	while (input[j] && input[j] != q)
		j++;
	if (input[j] == q)
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		*i = j;
		if (!word)
			perror_exit("strndup failed.\n");
		return (word);
	}
	perror_exit("quote not finished.\n");
}

char	*read_word(const char *input, int *i)
{
	char	*word;
	int		j;

	j = *i;
	while (input[j] && !ft_isspace(input[j]))
		j++;
	word = ft_strndup(&input[*i], j - *i);
	*i = j;
	return (word);
}

/**
 * ", ', $
 * 
 */
int	lexer_aux1(const char *input, t_token *tokens, int *_i, int idx)
{
	int	i;

	i = *_i;
	if (input[i] == '"')
	{
		tokens[idx].type = TKN_WORD_Q;
		tokens[idx].val = read_quote(input, &i);
		i++;
	}
	else if (input[i] == '\'')
	{
		tokens[idx].type = TKN_WORD;
		tokens[idx].val = read_quote(input, &i);
		i++;
	}
	else if (input[i] == '$')
	{
		tokens[idx].type = TKN_ENVAR;
		tokens[idx].val = read_word(input, &i);
	}
	idx++;
	*_i = i;
	return (idx);
}

/**
 * < << > >>
 */
int	lexer_aux2(const char *input, t_token *tokens, int *_i, int idx)
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

int	lexer(const char *input, t_token *tokens)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		// ft_printf("%i:%c\n", i, input[i]);
		if (input[i] == '"' || input[i] == '\'' || input[i] == '$')
			idx = lexer_aux1(input, tokens, &i, idx);
		else if (input[i] == '|')
		{
			tokens[idx++].type = TKN_PIPE;
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			idx = lexer_aux2(input, tokens, &i, idx);
		else if (input[i])
		{
			tokens[idx].type = TKN_WORD;
			tokens[idx++].val = read_word(input, &i);
		}
	}
	return (idx);
}


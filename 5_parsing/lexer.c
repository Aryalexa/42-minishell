

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
			perror_exit("strndup: mem error.");
		return (word);
	}
	my_perror("syntax error: quote not finished.");
	return (NULL);
}

char	*read_word(const char *input, int *i)
{
	char	*word;
	int		j;

	j = *i;
	while (input[j] && !ft_isspace(input[j]) && input[j] != '|')
		j++;
	word = ft_strndup(&input[*i], j - *i);
	if (!word)
		perror_exit("strndup: mem error.");
	*i = j;
	return (word);
}

/**
 * tokenize ", ', $
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
	if (tokens[idx].val == NULL)
		return (-1);
	idx++;
	*_i = i;
	return (idx);
}

/**
 * tokenize < << > >>
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

void	update_token(t_token *tokens, int t_i, t_tokenType type, char *value)
{
	tokens[t_i].type = type;
	tokens[t_i].val = value;
}

int	lexer(const char *input, t_token *tokens)
{
	int	i;
	int	t_i;

	i = 0;
	t_i = 0;
	while (input[i] && t_i != -1)
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '"' || input[i] == '\'' || input[i] == '$')
			t_i = lexer_aux1(input, tokens, &i, t_i);
		else if (input[i] == '|')
		{
			tokens[t_i++].type = TKN_PIPE;
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			t_i = lexer_aux2(input, tokens, &i, t_i);
		else if (input[i])
			update_token(tokens, t_i++, TKN_WORD, read_word(input, &i));
		if (t_i >= MAX_TKNS)
			return (my_perror("error: too many tokens!"), -1);
	}
	return (t_i);
}


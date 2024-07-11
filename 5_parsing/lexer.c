

#include "parsing.h"

/**
 * tokenize ", ', $
 * 
 */
int	lexer_aux1(const char *input, t_token *tokens, int *_i, int idx)
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

int	update_token(t_token *tokens, int t_i, t_tokenType type, char *value)
{
	if (!value)
		return (-1);
	tokens[t_i].type = type;
	tokens[t_i].val = value;
	return t_i + 1;
}

int	lexer(const char *input, t_token *tokens)
{
	int	i;
	int	t_i;

	ft_memset(tokens, '\0', sizeof(t_token) * MAX_TKNS);
	i = 0;
	t_i = 0;
	while (input[i] && t_i != -1)
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '$')
			t_i = lexer_aux1(input, tokens, &i, t_i);
		else if (input[i] == '|')
		{
			tokens[t_i++].type = TKN_PIPE;
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			t_i = lexer_aux2(input, tokens, &i, t_i);
		else if (input[i])
			t_i = update_token(tokens, t_i, TKN_WORD, read_word(input, &i));
		if (t_i >= MAX_TKNS)
			return (my_perror("error: too many tokens!"), -1);
	}
	return (t_i);
}


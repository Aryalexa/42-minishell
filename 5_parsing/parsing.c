

#include "parsing.h"

/**
 * return the word without wrapping quotes
 */
char	*consume_quote(const char *input, int *i)
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
			perror_exit("strndup failed.\n"); //
		return (word);
	}
	perror_exit("quote not finished.\n");
}

char	*consume_word(const char *input, int *i)
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
int lexer_aux1(const char *input, t_token *tokens, int *_i, int idx)
{
	int	i;

	i = *_i;
	if (input[i] == '"')
	{
		tokens[idx].type = WORD_Q;
		tokens[idx].val = consume_quote(input, &i);
		i++;
	}
	else if (input[i] == '\'')
	{
		tokens[idx].type = WORD;
		tokens[idx].val = consume_quote(input, &i);
		i++;
	}
	else if (input[i] == '$')
	{
		i++;
		tokens[idx].type = ENVAR;
		tokens[idx].val = consume_word(input, &i);
	}
	idx++;
	*_i = i;
	return (idx);
}

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
		ft_printf("%i:%c\n", i, input[i]);
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
			tokens[idx].type = WORD;
			tokens[idx++].val = consume_word(input, &i);
		}
	}
	return (idx);
}

void main_parser()
{

	char *input = "  <in  \"'ls$USER'\" 'arg1 '$arg2'  |  543 'arg3' =fgf >> appendhere we $fd < file1 <<lim arg   ";
	ft_printf("%c\n",input[0]);
	t_token tokens[MAX_TKNS];

	int n = lexer(input, tokens);
	int i = 0;
	ft_printf("tokens %i\n", n);
	while (i < n)
	{
		ft_printf("%i:", i);
		if (tokens[i].type > 2)
			ft_printf("no val");
		else ft_printf(tokens[i].val);
		ft_printf(" ");
		ft_printf("%i", tokens[i].type);
		ft_printf("\n");
		i++;
	}

}

int main()
{
	main_parser();
}


/**
 * gcc 5_parsing/parsing.c 3_error/error.c 1_libft/libft.a 

 */
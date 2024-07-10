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

int	is_reserved(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*dup_clean_simplequotes(const char *str, int len)
{
	char	*res;
	int		i;
	int		j;

	if (ft_strchri(str, '\'') < len && ft_strchri(str, '\'') != -1)
	{
		if (len < 0)
			perror_exit("fatal error 345.");
		res = (char *)malloc(sizeof(char) * (len - 1));
		if (!res)
			perror_exit("malloc: mem error.");
		i = 0;
		j = 0;
		while (str[i] && i < len)
		{
			if (str[i] != '\'')
				res[j++] = str[i++];
			else
				i++;
		}
		res[j] = '\0';
		return (res);
	}
	else
		return (ft_strndup(str, len));
}

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
	word = dup_clean_simplequotes(&input[*i], j - *i);
	if (!word)
		perror_exit("strndup: mem error.");
	return (*i = j, word);
}

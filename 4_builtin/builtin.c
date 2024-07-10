

#include "builtin.h"


/**
 * return len
 */
int	expand_dollar(char *code, int *i, char **val)
{
	if (!code[*i + 1] || ft_isspace(code[*i + 1]))
	{
		*val = ft_strdup("$");
		(*i)++;
		return (1);
	}
	// USAR ENV
	(*i)++;
	while (code[*i] && !ft_isspace(code[*i]))
		(*i)++;
	*val = ft_strdup("DOLLAR"); //
	return (ft_strlen(*val));
}

/**
 * return len
 */
int	expand_quotes(char *code, int *i, char	*val)
{
	int		start;
	int		j;
	char	*dollar_val;

	j = 0;
	start = ++(*i);
	dollar_val = NULL;
	val = my_calloc(ft_strchri(&code[*i], '"') + 1, 1);
	ft_printf("---expand_quotes\n"); //
	while (code[*i] != '"')
	{
		if (code[*i] == '$')
		{
			j += expand_dollar(code, i, &dollar_val);
			val = ft_strjoin_inplace(val, dollar_val);
		}
		else
			val[j++] = code[*i++];
	}
	ft_printf("---expand_quotes\n"); //
	val = ft_strndup((const char *)&code[start], *i - start);
	return (ft_strlen(val));
}

/**
 * s1 new value is the onw s2 is pointing
 * frees old s1 value
 */
void	swap_and_free_strings(char *s1, char *s2)
{
	char	*aux;

	aux = s1;
	s1 = s2;
	free(aux);
}
/**
 * modify the code to its expansion
 * cases:
 * - " -> interprete
 * - $
 * - no nulo
 */
void	expand_token_val(char *code)
{
	int		i;
	char	*val;
	char	*aux_val;
	int		j;

	i = 0;
	j = 0;
	val = my_calloc(ft_strlen(code) + 1 , 1);
	aux_val = NULL;
	ft_printf("---begin expanding (%s)\n", code); //
	while (code[i])
	{
		if (code[i] == '"')
		{
			j += expand_quotes(code, &i, aux_val);
			ft_printf("end expand quotes\n"); //
			ft_printf("ini val %s\n", val); //
			ft_printf("ini aux_val %s\n", aux_val); //

			val = ft_strjoin_inplace(val, aux_val);
			ft_printf("joined %s\n", val); //

		}
		else if (code[i] == '$')
		{
			ft_printf("ENTRO\n");
			j += expand_dollar(code, &i, &aux_val);
			ft_printf("SALGO %i\n", i);
			// ft_printf(val);
			// ft_printf(aux_val);
			val = ft_strjoin_inplace(val, aux_val);
		}
		else
			val[j++] = code[i++];
		
	}
	ft_printf("end while. result val (%s)\n", val); //
	swap_and_free_strings(code, val); // BAD
	ft_printf("---end expanding (%s)\n", code); //
}

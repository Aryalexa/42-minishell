/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:13 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/04 00:17:17 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int	expand_quotes(char *text, int *i, char	**val, t_shcontext *env)
{
	int		j;
	char	q_char;

	j = 0;
	q_char = text[*i];
	env->open_quote = q_char;
	(*i)++;
	*val = my_calloc(ft_strchri(&text[*i], q_char) + 1, 1);
	while (text[*i] != q_char)
	{
		if (q_char == '"' && text[*i] == '$')
		{ //
			*val = ft_strjoin_inplace2(val, expand_dollar(text, &i, &j, env));
		} //
		else
		{
			*val = ft_strappendc_inplace(*val, text[(*i)++]);
			j++;
		}
	}
	(*val)[j] = '\0';
	(*i)++;
	env->open_quote = '\0';
	return (ft_strlen(*val));
}



char	*get_env_var(char *var_key, t_shcontext *env)
{
	char	*var_value;
	char	*aux;
	int		j;

	var_value = NULL;
	j = envvar_index(var_key, env);
	if (j == -1)
		return ((char *) my_calloc(1, 1));
	get_kv(env->env[j], &aux, &var_value);
	free(aux);
	return (var_value);
}

/**
 * if quotes are open, q_char is " OR ' , otherwise NULL
 * - input= $<quote> - we came from open quotes
 * - input = $<quote> - new open quotes
 * - input = $\0 OR $<reserved> OR $<space>
 * 
 */
int	expand_dollar_simple(char *text, int *i, char **val, char q_char)
{
	if (!text[*i + 1] || isreservedall(text[*i + 1])
		|| isspace(text[*i + 1]))
	{
		if (text[*i + 1] == q_char)
			*val = ft_strdup("$");
		else if (isquote(text[*i + 1]))
			*val = ft_strdup("");
		else
			*val = ft_strdup("$");
		return (1);
	}
	return (0);
}

/**
 * expands text and saves it in val
 * returns the lenght of val
 */
int	expand_dollar_aux(char *text, int *i, char **val, t_shcontext *env)
{
	char	*var;
	int		j;

	var = my_calloc(ft_strlen(text) + 1, 1);
	if (!text[*i + 1] || isreservedall(text[*i + 1])
		|| isspace(text[*i + 1]))
	{
		(*i)++;
		free(var);
		return (0);
	}
	else if (text[*i + 1] == '?')
	{
		(*i) += 2;
		*val = ft_itoa(env->status);
		free(var);
		return (ft_strlen(*val));
	}
	(*i)++;
	j = 0;
	while (text[*i] && ft_isalnum(text[*i]))
		var[j++] = text[(*i)++];
	*val = get_env_var(var, env);
	free(var);
	return (ft_strlen(*val));
}

/**
 * get envvar name.
 * it duplicates the name from the text and returns it,
 * it copies everything after the $ while is alphanum. 
 */
char	*get_varname(char *text, int *i, t_shcontext *env)
{
	char	*name;
	int		j;

	name = my_calloc(ft_strlen(text) + 1, 1);
	(*i)++;
	j = 0;
	while (text[*i] && ft_isalnum(text[*i]))
		name[j++] = text[(*i)++];
	return (name);
}

/**
 * A $ have been encountered so we try to expand the env var.
 * It starts with text[i] == '$'
 * @arg text	str to parse
 * @arg i		text index
 * @arg j		returns j + len(retval)
 * @arg env		context var
 * @return		str with the value of the envvar
 */
char	**expand_dollar(char *text, int *i, int *j, t_shcontext *env)
{
	char	*varname;
	char	*val;
	int		j;

	if (!text[*i + 1] || isreservedall(text[*i + 1]) || isspace(text[*i + 1]))
	{
		(*i)++;
		if (isquote(text[*i + 1]) && text[*i + 1] != env->open_quote)
			*val = ft_strdup("");
		else
			*val = ft_strdup("$");
		(*j)++;
		return (&val);
	}
	else if (text[*i + 1] == '?')
	{
		(*i) += 2;
		*val = ft_itoa(env->status);
	}
	else
	{
		varname = get_varname(text, i, env);
		*val = get_env_var(varname, env);
		free(varname);
	}
	*j += ft_strlen(val);
	return (&val);
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
	int		j;

	val = my_calloc(ft_strlen(text) + 1, 1);
	i = 0;
	j = 0; // para que sirve esto??
	while (text[i])
	{
		if (isquote(text[i]))
		{
			j += expand_quotes(text, &i, &aux_val, env);
			val = ft_strjoin_inplace2(&val, &aux_val);
		}
		else if ((text)[i] == '$')
		{ //
			// j += expand_dollar_simple(text, &i, &aux_val, '\0');
			// j += expand_dollar_aux(text, &i, &aux_val, env);
			// val = ft_strjoin_inplace(&val, aux_val);
			val = ft_strjoin_inplace2(&val, expand_dollar(text, &i, &j, env));
		} //
		else
		{
			val = ft_strappendc_inplace(val, text[i++]);
			j++;
		}
	}
	return (val);
}

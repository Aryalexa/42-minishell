/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:28 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 16:58:24 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*my_malloc(size_t size)
{
	void	*val;

	val = malloc(size);
	if (!val)
		my_perror_exit("malloc: mem error.");
	return (val);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*val;

	val = ft_calloc(count, size);
	if (!val)
		my_perror_exit("calloc: mem error.");
	return (val);
}

int	is_reserved(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_reserved_all(char c)
{
	if (c == '<' || c == '>' || c == '|'
		|| c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

/**
 * s1 new value is the onw s2 is pointing
 * frees old s1 value
 */
void	swap_and_free_strings(char **s1, char **s2)
{
	char	*aux;

	aux = *s1;
	*s1 = *s2;
	free(aux);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:28 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/16 14:46:29 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*my_malloc(size_t size)
{
	void	*val;

	val = malloc(size);
	if (!val)
		perror_exit("malloc: mem error.");
	return (val);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*val;

	val = ft_calloc(count, size);
	if (!val)
		perror_exit("calloc: mem error.");
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

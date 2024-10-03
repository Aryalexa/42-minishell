/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:28 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/02 18:36:24 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * is <, > or |
 */
int	is_reserved(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

/**
 * is <, >, |, " or '
 */
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

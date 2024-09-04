/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:28 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/21 13:20:21 by macastro         ###   ########.fr       */
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

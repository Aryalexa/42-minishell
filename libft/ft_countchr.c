/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:09:09 by macastro          #+#    #+#             */
/*   Updated: 2023/06/13 20:09:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countchr(const char *str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	int		count;

	count = 0;
	len = ft_strlen(str);
	if (len < n)
		n = len;
	i = 0;
	while (i < n)
		if (str[i++] == c)
			count++;
	return (count);
}

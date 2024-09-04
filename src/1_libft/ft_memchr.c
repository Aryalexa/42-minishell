/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:33:34 by macastro          #+#    #+#             */
/*   Updated: 2023/09/15 18:33:36 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The memchr() function locates the first occurrence of c (converted to an
    unsigned char) in string s. 
	A pointer to memory doe not have ending!

	RETURN VALUES
	The memchr() function returns a pointer to the byte located, or NULL if
	no such byte exists within n bytes.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}

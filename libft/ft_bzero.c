/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:27:03 by macastro          #+#    #+#             */
/*   Updated: 2023/09/15 18:27:38 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The bzero() function writes n zeroed bytes to the string s.  If n is
    zero, bzero() does nothing.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

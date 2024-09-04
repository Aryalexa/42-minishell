/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:50:05 by macastro          #+#    #+#             */
/*   Updated: 2024/07/10 21:39:08 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	char	*res;

	if (n < 0)
		n = ft_strlen(str);
	res = (char *)ft_calloc((n + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, n + 1);
	return (res);
}

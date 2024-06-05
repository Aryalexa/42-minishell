/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_times_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:49:38 by macastro          #+#    #+#             */
/*   Updated: 2023/06/12 15:49:40 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_times_fd(char c, int times, int fd)
{
	int	i;

	i = 0;
	while (i < times)
	{
		ft_putchar_fd(c, fd);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:35:45 by macastro          #+#    #+#             */
/*   Updated: 2024/08/02 13:19:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putarr_ints(int *ints, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%i\n", ints[i]);
		i++;
	}
}

void	ft_putarr_str(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_printf("%s\n", words[i]);
		i++;
	}
}

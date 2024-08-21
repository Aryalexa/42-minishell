/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:44 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/21 13:01:28 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
void	debug(char *msg)
{
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
	//1 > 2
	// ft_printf
	//reset 1
}

void	debug_int(char *name_desc, int n)
{
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " ", 1);
	ft_putnbr_fd(n, 2);
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
	//1 > 2
	// ft_printf
	//reset 1
}

void	debug_str(char *name_desc, char* str)
{
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " ", 1);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
	//1 > 2
	// ft_printf
	//reset 1
}

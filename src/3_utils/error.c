/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:45:44 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 19:56:47 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	my_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	my_perror_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	my_perror_exit_ok(char *msg, int err)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(err);
}

void	my_perr_arg(char *msg, char *var_name)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, var_name, ft_strlen(var_name));
	write(2, "\n", 1);
}

void	my_perr_arg_exit(char *msg, char *var_name)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, var_name, ft_strlen(var_name));
	write(2, "\n", 1);
	exit(1);
}

/**
 * 0 -in
 * 1 - out
 * 2 -err
 * open .. 3,4,5
 * 3 - file
 * 
 * 
 * i = dup(1) --> i = 4 // 
 * 4 - out 
 * 
 * 
 * dup2(3, 1) --> 3 new out
 * 1 - file
 * 
 * dup2(4, 1) --> 4 new out
 * 1 - out 
 * 
 */
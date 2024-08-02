/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/02 12:24:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		isoption(t_cmdnode node, char *option)
{
	int i;

	i = 1;
	while (i < node.argc)
	{
		if(ft_strcmp(node.argv[i], option)== 0)
			return(1);
		i++;
	}
	return (0);
}

void	exec_echo(t_cmdnode node, char *env[])
{
	(void)env;
	int i;

	i = 1;
	while(i < node.argc)
	{
		if(ft_strcmp(node.argv[i], "-n") != 0)
		{
			ft_putstr_fd(node.argv[i], 1);
			if( i < node.argc - 1)
				write(1, " ", 1);
		}
		i++;
	}
	if(!isoption(node, "-n"))
		write(1, "\n", 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 14:25:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	isoption(t_cmdnode node, char *option)
{
	int	i;

	i = 1;
	while (i < node.argc)
	{
		if (ft_strcmp(node.argv[i], option) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exec_echo(t_cmdnode node, t_shcontext *env)
{
	int	i;

	(void)env;
	i = 1;
	while (i < node.argc)
	{
		if (ft_strcmp(node.argv[i], "-n") != 0)
		{
			ft_putstr_fd(node.argv[i], 1);
			if (i < node.argc - 1)
				write(1, " ", 1);
		}
		i++;
	}
	if (!isoption(node, "-n"))
		write(1, "\n", 1);
}

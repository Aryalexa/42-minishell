/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/17 16:13:25 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_echo(t_cmdnode node, t_shcontext *env)
{
	int	i;
	int	option_n;

	(void)env;
	option_n = 0;
	i = 1;
	while ((i < node.argc) && (ft_strcmp(node.argv[i], "-n") == 0))
	{
		option_n = 1;
		i++;
	}
	while (i < node.argc)
	{
		ft_putstr_fd(node.argv[i], 1);
		if ((i < node.argc - 1) && node.argv[i][0])
			write(1, " ", 1);
		i++;
	}
	if (!option_n)
		write(1, "\n", 1);
	return (0);
}

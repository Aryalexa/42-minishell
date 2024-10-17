/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/17 16:17:26 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_exit(t_cmdnode node, t_shcontext *env)
{
	int	st;

	if (node.argc != 1 && node.argc != 2)
	{
		my_perror("exit\nbash: exit: too many arguments");
		return (1);
	}
	if (node.argc == 2)
	{
		if (ft_atoi_secure(node.argv[1], &st))
			st = st % 255;
		else
			my_perror_exit_st("exit\nerror exit: numeric argument required", 2);
	}
	else
		st = env->status;
	ft_free_arrstr(env->env);
	free_node(node);
	if (env->nopipe)
		ft_printf("exit\n");
	exit(st);
}

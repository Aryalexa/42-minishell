/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/13 19:02:49 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env_style(char *line)
{
	int	pos;

	pos = ft_strchri(line, '=');
	if (pos != -1)
		ft_printf("%s\n", line);
}

void	exec_env(t_cmdnode node, t_env *env)
{
	int	i;

	(void)node;
	i = 0;
	while (env->env[i])
	{
		print_env_style(env->env[i]);
		i++;
	}
}

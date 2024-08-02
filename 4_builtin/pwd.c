/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/02 14:01:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_pwd(char *env[])
{
	int		i;
	
	i = 0;
	while (ft_strnstr(env[i], "PWD", 3) == NULL)
		i++;
	return(&env[i][4]);
}

void	exec_pwd(t_cmdnode node,  t_env env)
{
	(void)	node;
	char	*path;
	
	path = get_pwd(env.env);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
}
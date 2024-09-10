/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 14:25:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_pwd(t_cmdnode node, t_shcontext *env)
{
	char	cwd[PATH_MAX];

	(void) node;
	(void) env;
	getcwd(cwd, PATH_MAX);
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
}

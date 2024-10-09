/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 14:18:43 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_pwd(t_cmdnode node, t_shcontext *env)
{
	char	*pwd;

	(void) node;
	(void) env;
	pwd = get_env_var("PWD", env);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	return (0);
}

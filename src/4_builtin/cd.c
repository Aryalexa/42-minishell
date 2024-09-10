/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 14:25:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * get abs path
 */
int	checkpath(char	*path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

/**
 * Change directory.
 * it calls chdir and change the env var PWD
 */
void	exec_cd(t_cmdnode node, t_shcontext *env)
{
	char	cwd[PATH_MAX];

	if (node.argc == 1)
		return ;
	if (node.argc > 2)
	{
		my_perror("Error. Too many arguments.");
		return ;
	}
	if (!checkpath(node.argv[1]))
	{
		my_perror("Error. No such file or directory.");
		return ;
	}
	if (chdir(node.argv[1]) != 0)
	{
		my_perror("Error. Failed to change directory.");
		return ;
	}
	getcwd(cwd, PATH_MAX);
	update_envvar("PWD", cwd, env);
}

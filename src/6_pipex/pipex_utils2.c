/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:00:00 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 16:05:20 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * return the number of builtin
 * return -1 if not builtin
 */
int	check_builtin(t_cmdnode node)
{
	int			i;
	const char	built_ins_names[7][7] = {"echo", "exit", "pwd",
		"export", "unset", "env", "cd"};

	if (!node.cmd)
		return (-1);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(t_cmdnode node, t_shcontext *env)
{
	int			i;
	const t_FP	built_ins[7] = {&exec_echo, &exec_exit,
		&exec_pwd, &exec_export, &exec_unset, &exec_env, &exec_cd};

	i = check_builtin(node);
	if (i >= 0)
		return (built_ins[i](node, env));
	return (0);
}

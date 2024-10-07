/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:00:00 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/07 17:17:31 by macastro         ###   ########.fr       */
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

/**
 * infile? then file is new in
 */
int	process_infiles(int n, t_infile	*infiles)
{
	int			j;
	int			fdin;

	j = 0;
	j = 0;
	while (j < n)
	{
		if (infiles[j].type == F_HEREDOC)
		{
			dup2(infiles[j].fd, STDIN_FILENO);
			close(infiles[j].fd);
		}
		else
		{
			fdin = open(infiles[j].filename_delim, O_RDONLY);
			if (fdin < 0)
				return (my_perror("*input file error at open"), 1);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		j++;
	}
	return (0);
}

/**
 * outfile? then file new out
 * @return 0 if success, -1 otherwise
 */
int	process_outfiles(int n, t_outfile *outfiles)
{
	int	j;
	int	fdout;

	j = 0;
	while (j < n)
	{
		if (outfiles[j].type == F_APPEND)
			fdout = open(outfiles[j].filename,
					O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fdout = open(outfiles[j].filename,
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fdout < 0)
		{
			my_perror("error at open an outfile");
			return (1);
		}
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		j++;
	}
	return (0);
}

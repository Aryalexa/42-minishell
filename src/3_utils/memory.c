/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:46:28 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/10 13:48:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*my_malloc(size_t size)
{
	void	*val;

	val = malloc(size);
	if (!val)
		my_perror_exit("malloc: mem error.");
	return (val);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*val;

	val = ft_calloc(count, size);
	if (!val)
		my_perror_exit("calloc: mem error.");
	return (val);
}

/**
 * free cmd, argv, infiles and outfiles
 */
void	free_node(t_cmdnode node)
{
	int	j;

	if (node.cmd)
		free(node.cmd);
	j = 0;
	while (j < node.argc)
		free(node.argv[j++]);
	j = 0;
	while (j < node.redir.n_in)
		free(node.redir.infiles[j++].filename_delim);
	j = 0;
	while (j < node.redir.n_out)
		free(node.redir.outfiles[j++].filename);
}

void	free_nodes(int n_nodes, t_cmdnode *nodes)
{
	int	i;

	i = 0;
	debug("free_nodes in\n");
	while (i < n_nodes)
	{
		free_node(nodes[i]);
		i++;
	}
}

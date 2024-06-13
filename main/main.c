/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:44:11 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/13 14:28:21 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ls 
 */
t_node *crea_ls()
{
    int n = 1;
    t_node *nodes = malloc(n * sizeof(n));

    nodes[0].cmd = "ls";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    //nodes[0].redir;
    return nodes;
    
}

/**
 * cat t1 > t2
 */
t_node *crea_cat1()
{
    int n = 1;
    t_node *nodes = malloc(n * sizeof(n));

    nodes[0].cmd = "cat";
    nodes[0].argc = 2;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].argv[0] = nodes[0].cmd;
    nodes[0].argv[0] = "t1";

    nodes[0].redir.n_in = 0;
    nodes[0].redir.n_out = 1;
    nodes[0].redir.outfiles = malloc(nodes[0].redir.n_out * sizeof(t_outfile));
    nodes[0].redir.outfiles[0].filename = "t2";
    nodes[0].redir.outfiles[0].type = F_OUT

    return nodes;
    
}

int	main(int argc, char *argv[], char *envp[])
{
    t_node *nodes = crea_ls();


    my_pipex(nodes, envp);
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:44:11 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/05 19:15:58 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ls 
 */
void    crea_ls(t_cmdnode nodes[MAX_NODES])
{
    nodes[0].cmd = "ls";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].redir.n_in = 0;
    nodes[0].redir.n_out = 0;
    
}

void    crea_ls_out(t_cmdnode nodes[MAX_NODES])
{
    nodes[0].cmd = "ls";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].redir.n_in = 0;
    nodes[0].redir.n_out = 1;
    nodes[0].redir.outfiles[0].filename = "ls_out";
    nodes[0].redir.outfiles[0].type = F_OUT;
    
}

void    crea_cmd_solo(t_cmdnode nodes[MAX_NODES])
{
    //nodes[0].cmd = "echo";
    nodes[0].cmd = "/usr/bin/echo";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].redir.n_in = 0;
    nodes[0].redir.n_out = 0;

}

/*
<< a cat
*/
void    crea_heredoc(t_cmdnode nodes[MAX_NODES])
{
    nodes[0].cmd = "cat";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].redir.n_in = 1;
    nodes[0].redir.infiles[0].filename_delim = "a";
    nodes[0].redir.infiles[0].type = F_HEREDOC;
    nodes[0].redir.n_out = 0;
    
}

/**
 * infiles y outfiles - complicado
 * < f1 < f2 << a wc >> f3 > f4 > f5
 */
void    crea_inoutfiles(t_cmdnode nodes[MAX_NODES])
{
    nodes[0].cmd = "wc";
    nodes[0].argc = 1;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].redir.n_in = 3;
    nodes[0].redir.infiles[0].filename_delim = "playground/f1";
    nodes[0].redir.infiles[0].type = F_IN;
    nodes[0].redir.infiles[1].filename_delim = "playground/f2";
    nodes[0].redir.infiles[1].type = F_IN;
    nodes[0].redir.infiles[2].filename_delim = "a";
    nodes[0].redir.infiles[2].type = F_HEREDOC;
    nodes[0].redir.n_out = 3;
    nodes[0].redir.outfiles[0].filename = "playground/f3";
    nodes[0].redir.outfiles[0].type = F_APPEND;
    nodes[0].redir.outfiles[1].filename = "playground/f4";
    nodes[0].redir.outfiles[1].type = F_OUT;
    nodes[0].redir.outfiles[2].filename = "playground/f5";
    nodes[0].redir.outfiles[2].type = F_OUT;
    
}
/**
 * cat t1 > t2
 */

t_cmdnode *crea_cat1()
{
    int n = 1;
    t_cmdnode *nodes = malloc(n * sizeof(n));

    nodes[0].cmd = "cat";
    nodes[0].argc = 2;
    nodes[0].argv = malloc(nodes[0].argc * sizeof(char));
    nodes[0].argv[0] = nodes[0].cmd;
    nodes[0].argv[0] = "t1";

    nodes[0].redir.n_in = 0;
    nodes[0].redir.n_out = 1;
    nodes[0].redir.outfiles[0].filename = "t2";
    nodes[0].redir.outfiles[0].type = F_OUT;

    return nodes;
 
}

char **create_env(char *envp2[])
{
    char	**env;
    int     size;

	size = 0;
	while (envp2[size] != NULL)
		size++;
	env = malloc((size + 1) *sizeof(char *));
	if (!env)
        return NULL;
	size = 0;
	while (envp2[size] != NULL)
	{
        env[size] = ft_strdup(envp2[size]);
        if (env[size] == NULL)
            return NULL;
            //perror(strdup); y liberar memoria
		size++;
	}
    env[size] = NULL;
    return(env);
}

int	main(int argc, char *argv[], char *envp[])
{
    char **env;
    t_cmdnode nodes[MAX_NODES];

    (void) argc;
    (void) argv;
    env = create_env(envp);
    crea_inoutfiles(nodes);
    my_pipex(1, nodes, env);
}
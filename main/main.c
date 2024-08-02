/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:09:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/02 14:07:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(char *envp2[])
{
	char	**env;
	int		size;

	size = 0;
	while (envp2[size] != NULL)
		size++;
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	size = 0;
	while (envp2[size] != NULL)
	{
		env[size] = ft_strdup(envp2[size]);
		if (env[size] == NULL)
			return (NULL);
		size++;
	}
	env[size] = NULL;
	return (env);
}

int	run_parser(char *input, t_cmdnode *nodes)
{
	int		n_t;
	int		n_n;
	t_token	tokens[MAX_TKNS];

	n_t = lexer(input, tokens);
	if (n_t < 0)
		return (-1);
	n_n = parse_tokens(tokens, n_t, nodes);
	free_tokens(tokens, n_t);
	return (n_n);
}

int	main(int argc, char **argv, char *envp[])
{
	t_env 		env;
	char		*input;
	t_cmdnode	nodes[MAX_NODES];
	int			n_nodes;

	env.envp = envp;
	env.env = create_env(envp);

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline(ANSI_COLOR_MAGENTA "minishell> " ANSI_COLOR_RESET);
		if (input)
			add_history(input);
		
		//Ctrl+D and NULL management to exit program //if (input == NULL)
		n_nodes = run_parser(input, nodes);

		if (n_nodes < 0)
			ft_printf("syntax error: no exec\n");
		else
		{
			ft_printf(ANSI_COLOR_CYAN "execution call\n" ANSI_COLOR_RESET);
			my_pipex(n_nodes, nodes, env);
			free_nodes(n_nodes, nodes);
		}
		free(input);
	}
	return (0);
}

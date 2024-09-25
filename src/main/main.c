/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:09:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/25 16:14:19 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * the original env that main receives has a null terminator
 * This creates a copy and returns the env and the number of items.
 * The copy does not have a null terminator.
 */
char	**create_env(char *env_src[], int *save_size)
{
	char	**env;
	int		size;

	size = 0;
	while (env_src[size] != NULL)
		size++;
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	size = 0;
	while (env_src[size] != NULL)
	{
		env[size] = ft_strdup(env_src[size]);
		if (env[size] == NULL)
			return (NULL);
		size++;
	}
	env[size] = NULL;
	*save_size = size + 1;
	return (env);
}

int	run_parser(char *input, t_cmdnode *nodes, t_shcontext *env)
{
	int		n_t;
	int		n_n;
	t_token	tokens[MAX_TKNS];

	n_t = lexer(input, tokens);
	if (n_t < 0)
		return (-1);
	n_n = parse_tokens(tokens, n_t, nodes, env);
	free_tokens(tokens, n_t);
	return (n_n);
}

void	run_command(char *input, t_shcontext *env)
{
	t_cmdnode	nodes[MAX_NODES];
	int			n_nodes;

	n_nodes = run_parser(input, nodes, env);
	if (n_nodes < 0)
		ft_printf("syntax error: no exec\n");
	else
	{
		debug(ANSI_COLOR_CYAN "execution call\n" ANSI_COLOR_RESET); //
		run_exec(n_nodes, nodes, env);
		free_nodes(n_nodes, nodes);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_shcontext	env;
	char		*input;

	env.o_env = envp;
	env.env = create_env(envp, &env.n_env);
	env.status = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		signal_main();
		debug("🌵MAIN - signal_main");
		if (isatty(STDIN_FILENO))
		{
			input = readline(ANSI_COLOR_MAGENTA "minishell> " ANSI_COLOR_RESET);
			if (!input)
				my_perror_exit("exit");
			else
				add_history(input);
		}
		else
			input = get_next_line(STDIN_FILENO);
		run_command(input, &env);
		free(input);
	}
	return (0);
}

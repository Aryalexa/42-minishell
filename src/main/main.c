/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:09:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 19:07:17 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigintsrc;

/**
 * the original env that main receives has a null terminator
 * This creates a copy and returns the env and the number of items.
 * The copy does not have a null terminator.
 */
static char	**dup_env(char *env_src[], int *save_size)
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

static t_shcontext	create_env(char *envp[])
{
	t_shcontext	env;

	env.o_env = envp;
	env.env = dup_env(envp, &env.n_env);
	env.status = 0;
	return (env);
}

static int	run_parser(char *input, t_cmdnode *nodes, t_shcontext *env)
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

static void	run_command(char *input, t_shcontext *env)
{
	t_cmdnode	nodes[MAX_NODES];
	int			n_nodes;

	n_nodes = run_parser(input, nodes, env);
	if (n_nodes < 0)
		ft_printf("syntax error: no exec\n");
	else
	{
		run_exec(n_nodes, nodes, env);
		free_nodes(n_nodes, nodes);
	}
}

/**
 * MAIN
 * - if input is null -> ctrl d -> exit
 */
int	main(int argc, char **argv, char *envp[])
{
	t_shcontext	env;
	char		*input;

	env = create_env(envp);
	(void)argc, (void)argv;
	while (1)
	{
		g_sigintsrc = 0;
		signal_main();
		if (isatty(STDIN_FILENO))
		{
			input = readline(ANSI_COLOR_MAGENTA "minishell> " ANSI_COLOR_RESET);
			if (g_sigintsrc == 1)
				env.status = 130;
			if (!input)
				my_perror_exit("exit");
			if (input[0] != '\0')
				add_history(input);
		}
		else
			input = get_next_line(STDIN_FILENO);
		run_command(input, &env);
		free(input);
	}
	return (0);
}

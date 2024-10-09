/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:09:17 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/09 14:35:44 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint_i;

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

	if (!input || !input[0])
		return ;
	n_nodes = run_parser(input, nodes, env);
	if (n_nodes < 0)
		ft_printf("syntax error: no exec\n");
	else
	{
		if (n_nodes == 1)
			env->nopipe = 1;
		run_exec(n_nodes, nodes, env);
		free_nodes(n_nodes, nodes);
	}
	env->nopipe = 0;
}

/**
 * MAIN
 * - using terminal: isatty(STDIN_FILENO) == TRUE
 * - if input is null -> ctrl d -> exit
 *
 */
int	main(int argc, char **argv, char *envp[])
{
	t_shcontext	env;
	char		*input;

	env = create_context(envp);
	(void)argc, (void)argv;
	while (1)
	{
		g_sigint_i = 0;
		signal_main();
		if (isatty(STDIN_FILENO))
		{
			input = readline(ANSI_COLOR_MAGENTA "minishell> " ANSI_COLOR_RESET);
			if (g_sigint_i == 1)
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

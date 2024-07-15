

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
		env[size] = strdup(envp2[size]);
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
	//print_tokens(tokens, n_t);
	n_n = parse_tokens(tokens, n_t, nodes);
	print_nodes(nodes, n_n);
	return (n_n);
}

/*Begins minishell and checks the input*/
int	main(int argc, char **argv, char *envp[])
{
	char		**env;
	char		*input;
	t_cmdnode	nodes[MAX_NODES];
	int			n_nodes;


	env = create_env(envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline(ANSI_COLOR_MAGENTA "minishell> " ANSI_COLOR_RESET);
		if (input)
			add_history(input);

		//Ctrl+D and NULL management to exit program
		//if (input == NULL)
		n_nodes = run_parser(input, nodes);
		// ya tengo los nodos para ejecutar!
		if (n_nodes < 0)
			ft_printf("syntax error: no exec\n");
		else
		{
			ft_printf(ANSI_COLOR_CYAN "execution call\n" ANSI_COLOR_RESET);
			my_pipex(n_nodes, nodes, env);
		}
		free(input);
	}
	return (0);
}




#include "minishell.h"


int run_parser(char *input, t_cmdnode *nodes)
{
	int		n_t;
	int		n_n;
	t_token	tokens[MAX_TKNS];

	//char *input = "  <in  \"'ls$USER'\" 'arg1 '$arg2'  |  543 'arg3' =fgf >> appendhere we $fd < file1 <<lim arg   ";
	//char *input = " ls . $ass '< inf' | <    inf2 <<a cmd2 > s >s2 >>append arg11";

	n_t = lexer(input, tokens);
	if (n_t < 0)
		return (-1);
	
	print_tokens(tokens, n_t);
	n_n = parse_tokens(tokens, n_t, nodes);
	print_nodes(nodes, n_n);
	return (n_n);
}

/*Begins minishell and checks the input*/
int	main(int argc, char **argv)
{
	char		*input;
	t_cmdnode	nodes[MAX_NODES];
	int			n_nodes;

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
			ft_printf("execution call\n");
		free(input);
	}
	return (0);
}


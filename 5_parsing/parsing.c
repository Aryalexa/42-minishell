

#include "parsing.h"

void print_tokens(t_token *tokens, int n)
{
	int i = 0;
	ft_printf("#tokens %i\n", n);
	while (i < n)
	{
		ft_printf("%i:", i);
		if (tokens[i].type > 2)
			ft_printf("no val");
		else ft_printf(tokens[i].val);
		ft_printf(" ");
		ft_printf("%i", tokens[i].type);
		ft_printf("\n");
		i++;
	}
}

void print_nodes(t_cmdnode *nodes, int n)
{
	int i = 0;
	int j;
	ft_printf("#nodes %i----\n", n);
	while (i < n)
	{
		ft_printf("nodes #%i\n", i);

		// cmd
		if (nodes[i].cmd)
			ft_printf("cmd:%s\n", nodes[i].cmd);
		else
			ft_printf("no cmd\n");
		// args
		j = 0;
		while (j < nodes[i].argc)
		{
			ft_printf("arg %i:%s\n", j, nodes[i].argv[j]);
			j++;
		}
		// redirs in
		j = 0;
		while (j < nodes[i].redir.n_in)
		{
			ft_printf("inf %i:%s", j, nodes[i].redir.infiles[j].filename_delim);
			if (nodes[i].redir.infiles[j].type == F_HEREDOC)
				ft_printf("(<<)\n");
			else if (nodes[i].redir.infiles[j].type == F_IN)
				ft_printf("(<)\n");
			else
				ft_printf("error\n");
			j++;
		}
		// redirs out
		j = 0;
		while (j < nodes[i].redir.n_out)
		{
			ft_printf("outf %i:%s", j, nodes[i].redir.outfiles[j].filename);
			if (nodes[i].redir.outfiles[j].type == F_APPEND)
				ft_printf("(>>)\n");
			else if (nodes[i].redir.outfiles[j].type == F_OUT)
				ft_printf("(>)\n");
			else
				ft_printf("error\n");
			j++;
		}


		i++;
	}
}
void main_parser()
{
	t_token tokens[MAX_TKNS];
	t_cmdnode nodes[MAX_CMDS];

	//char *input = "  <in  \"'ls$USER'\" 'arg1 '$arg2'  |  543 'arg3' =fgf >> appendhere we $fd < file1 <<lim arg   ";
	char *input = " ls . $ass '< inf' | <    inf2 <<a cmd2 > s >s2 >>append arg11";
	//ft_printf("%c\n",input[0]);

	int n_t = lexer(input, tokens);
	print_tokens(tokens, n_t);

	int n_n = parse_tokens(tokens, n_t, nodes);
	print_nodes(nodes, n_n);


}

int main()
{
	main_parser();
}


/**
 * 
 * gcc 5_parsing/parsing.c 5_parsing/lexer.c 5_parsing/parser.c 4_builtin/builtin.c 3_error/error.c 1_libft/libft.a


 */
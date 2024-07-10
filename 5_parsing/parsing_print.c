

#include "parsing.h"

void	print_token(t_token token)
{
	if (token.type > 2)
		ft_printf("no val");
	else
		ft_printf(token.val);
	ft_printf(" ");
	ft_printf("%i", token.type);
	ft_printf("\n");
}

void	print_tokens(t_token *tokens, int n)
{
	int i = 0;
	ft_printf("#tokens %i\n", n);
	while (i < n)
	{
		ft_printf("%i:", i);
		print_token(tokens[i]);
		i++;
	}
}

void	print_nodes(t_cmdnode *nodes, int n)
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

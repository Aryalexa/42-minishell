
#include "parsing.h"

void	check_word_and_vars(t_token token, t_cmdnode *node)
{
	if (token.type == TKN_WORD || token.type == TKN_WORD_Q || token.type == TKN_ENVAR)
	{
		if (token.type == TKN_WORD_Q || token.type == TKN_ENVAR) // resolve expansions
			expand(token.val);
		if (!node->cmd)
		{
			ft_printf("cmd found: %s\n", token.val);
			node->cmd = token.val;
			node->argc = 0;
		}
		else
		{
			ft_printf("arg found: %s\n", token.val);
			node->argv[node->argc] = token.val;
			node->argc++;
			if (node->argc > MAX_ARGS)
				perror_exit("max of args sobrepasado!"); // free?
		}
	}
}

void	read_file(t_token token, t_cmdnode *node, int is_infile)
{
	if (token.type == TKN_WORD_Q || token.type == TKN_ENVAR) // resolve expansions
		expand(token.val);
	if (is_infile)
	{
		ft_printf("infile found: %s\n", token.val);
		node->redir.infiles[node->redir.n_in].filename_delim = token.val;
	}
	else
	{
		ft_printf("outfile found: %s\n", token.val);
		node->redir.outfiles[node->redir.n_out].filename = token.val;
	}
}

void	check_infiles(t_token *tokens, t_cmdnode *node, int *t, int n_tokens)
{
	if (tokens[*t].type == TKN_LT || tokens[*t].type == TKN_HRDC)
	{
		if (tokens[*t].type == TKN_LT)
			node->redir.infiles[node->redir.n_in].type = F_IN;
		if (tokens[*t].type == TKN_HRDC)
			node->redir.infiles[node->redir.n_in].type = F_HEREDOC;
		if (++(*t) > n_tokens)
			perror_exit("syntax error 1!"); // free?
		if (tokens[*t].type == TKN_WORD || tokens[*t].type == TKN_WORD_Q || tokens[*t].type == TKN_ENVAR)
			read_file(tokens[*t], node, 1);
		else
			perror_exit("syntax error 2!"); // free?
		node->redir.n_in++;
	}
}

void	check_outfiles(t_token *tokens, t_cmdnode *node, int *t, int n_tokens)
{
	if (tokens[*t].type == TKN_GT || tokens[*t].type == TKN_APPD)
	{
		if (tokens[*t].type == TKN_GT)
			node->redir.outfiles[node->redir.n_out].type = F_OUT;
		if (tokens[*t].type == TKN_APPD)
			node->redir.outfiles[node->redir.n_out].type = F_APPEND;
		if (++(*t) > n_tokens)
			perror_exit("syntax error!"); // free?
		if (tokens[*t].type == TKN_WORD || tokens[*t].type == TKN_WORD_Q || tokens[*t].type == TKN_ENVAR)
			read_file(tokens[*t], node, 0);
		else
			perror_exit("syntax error!"); // free?
		node->redir.n_out++;
		
	}
}

/**
 * builds command nodes
 * returns number of nodes
 */
int    parse_tokens(t_token *tokens, int n_tokens, t_cmdnode *nodes)
{
	int t;
	int n;

	ft_memset(nodes, '\0', sizeof(t_cmdnode) * MAX_CMDS);
	n = 0;
	t = 0;
	while (t < n_tokens)
	{
		check_word_and_vars(tokens[t], &nodes[n]);
		check_infiles(tokens, &nodes[n], &t, n_tokens);
		check_outfiles(tokens, &nodes[n], &t, n_tokens);
		if (tokens[t].type == TKN_PIPE)
			n++;
		t++;
	}
	n++;
	return (n);


}

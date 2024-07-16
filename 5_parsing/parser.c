/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:58:04 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/16 15:13:49 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_word_and_vars(t_token token, t_cmdnode *node)
{
	if (token.type == TKN_WORD || token.type == TKN_ENVAR)
	{
		//ft_printf("token BEFORE: %s, %i\n", token.val, token.type);
		expand_token_val(&token.val);
		//ft_printf("token AFTER: %s\n", token.val);
		if (!node->cmd)
		{
			// ft_printf("cmd found: %s\n", token.val); //
			node->cmd = token.val;
			node->argv[0] = token.val;
			node->argc = 1;
		}
		else
		{
			// ft_printf("arg found: %s\n", token.val); //
			node->argv[node->argc] = token.val;
			node->argc++;
			if (node->argc >= MAX_ARGS)
			{
				my_perror("error: too many args!"); // free?
				return (-1);
			}
		}
	}
	return (0);
}

void	read_file(t_token token, t_cmdnode *node, int is_infile)
{
	if (token.type == TKN_WORD || token.type == TKN_ENVAR)
		expand_token_val(&token.val);
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

int	check_infiles(t_token *tokens, t_cmdnode *node, int *t, int n_tokens)
{
	if (tokens[*t].type == TKN_LT || tokens[*t].type == TKN_HRDC)
	{
		if (tokens[*t].type == TKN_LT)
			node->redir.infiles[node->redir.n_in].type = F_IN;
		if (tokens[*t].type == TKN_HRDC)
			node->redir.infiles[node->redir.n_in].type = F_HEREDOC;
		if (++(*t) >= n_tokens)
		{
			my_perror("syntax error: missing value after `<'/'<<' at the end!"); // free?
			return (-1);
		}
		if (tokens[*t].type == TKN_WORD || tokens[*t].type == TKN_ENVAR)
			read_file(tokens[*t], node, 1);
		else
		{
			my_perror("syntax error: missing value after `<'/'<<'!"); // free?
			return (-1);
		}
		node->redir.n_in++;
		if (node->redir.n_in >= MAX_FILES)
			return (my_perror("error: too many infiles!"), -1);
	}
	return (0);
}

int	check_outfiles(t_token *tokens, t_cmdnode *node, int *t, int n_tokens)
{
	if (tokens[*t].type == TKN_GT || tokens[*t].type == TKN_APPD)
	{
		if (tokens[*t].type == TKN_GT)
			node->redir.outfiles[node->redir.n_out].type = F_OUT;
		if (tokens[*t].type == TKN_APPD)
			node->redir.outfiles[node->redir.n_out].type = F_APPEND;
		if (++(*t) >= n_tokens)
		{
			my_perror("syntax error: missing file after `>'/'>>' at the end!"); // free
			return (-1);
		}
		if (tokens[*t].type == TKN_WORD || tokens[*t].type == TKN_ENVAR)
			read_file(tokens[*t], node, 0);
		else
		{
			my_perror("syntax error: missing file after `>'/'>>'!"); // free
			return (-1);
		}
		node->redir.n_out++;
		if (node->redir.n_out >= MAX_FILES)
			return (my_perror("error: too many outfiles!"), -1);
	}
	return (0);
}

int	check_pipe(t_token *tokens, int t, int n_tokens, int *n)
{
	if ((t == 0 && tokens[t].type == TKN_PIPE)
		|| (t == n_tokens - 1 && tokens[t].type == TKN_PIPE))
	{
		my_perror("syntax error: bad pipe usage!");
		return (-1);
	}
	if (tokens[t].type == TKN_PIPE)
	{
		if (t + 1 < n_tokens && tokens[t + 1].type == TKN_PIPE)
		{
			my_perror("syntax error: bad pipe usage!");
			return (-1);
		}
		(*n)++;
		if (*n >= MAX_NODES)
			return (my_perror("error: too many command nodes!"), -1);
	}
	return (0);
}

/**
 * builds command nodes
 * returns number of nodes
 */
int	parse_tokens(t_token *tokens, int n_tokens, t_cmdnode *nodes)
{
	int	t;
	int	n;
	int	ok;

	ft_memset(nodes, '\0', sizeof(t_cmdnode) * MAX_NODES);
	n = 0;
	t = 0;
	ok = 1;
	while (t < n_tokens && ok)
	{
		ok = ok && (check_word_and_vars(tokens[t], &nodes[n]) == 0);
		ok = ok && (check_infiles(tokens, &nodes[n], &t, n_tokens) == 0);
		ok = ok && (check_outfiles(tokens, &nodes[n], &t, n_tokens) == 0);
		ok = ok && (check_pipe(tokens, t, n_tokens, &n) == 0);
		t++;
	}
	n++;
	if (!ok)
		return (-1);
	return (n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:01:03 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 18:51:10 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define MAX_TKNS   101

# include "../1_libft/libft.h"
# include "../2_structs/structs.h"
# include "../3_utils/utils.h"
# include "../4_builtin/builtin.h"

typedef enum e_tokenType
{
	TKN_WORD,
	TKN_ENVAR,
	TKN_PIPE,
	TKN_GT,
	TKN_LT,
	TKN_HRDC,
	TKN_APPD,
	N_TOKENTYPE
}	t_tokenType;

typedef struct s_token
{
	t_tokenType	type;
	char		*val;
}	t_token;

int		lexer(const char *input, t_token *tokens);
int		parse_tokens(t_token *tokens, int n_tokens, t_cmdnode *nodes);
void	print_nodes(t_cmdnode *nodes, int n);
void	print_tokens(t_token *tokens, int n);
void	print_token(t_token token);
char	*read_word(const char *input, int *i);
void	free_tokens(t_token *tokens, int n_tokens);

#endif


#ifndef PARSING_H
# define PARSING_H

# include "../3_error/error.h"
# include "../1_libft/libft.h"
# include "../2_structs/structs.h"
# include "../4_builtin/builtin.h"


# define MAX_TKNS   101


typedef enum e_tokenType
{
	TKN_WORD,
	TKN_WORD_Q,
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

#endif
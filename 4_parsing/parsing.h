

#ifndef PARSING_H
# define PARSING_H

#include "../3_error/error.h"
#include "../1_libft/libft.h"


# define MAX_TKNS   100


typedef enum e_tokenType
{
	// CMD,
	// ARG,
	// TKN_FILE,
	WORD,
	WORD_Q,

	ENVAR, // DOLLAR + WORD

	TKN_PIPE,

	TKN_GT,
	TKN_LT,
	TKN_HRDC,
	TKN_APPD,

	N_TOKENTYPE
} t_tokenType;

typedef struct s_token
{
	t_tokenType type;
	char *       val;
}   t_token;

#endif
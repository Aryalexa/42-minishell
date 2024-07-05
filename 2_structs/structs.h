/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:45:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/05 19:37:23 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../1_libft/libft.h"


# define MAX_NODES	100
# define MAX_ARGS	100
# define MAX_FILES	100

typedef enum e_built_ins
{
	ECHO,		// 0
	CD,			// 1
	PWD,		// 2
	EXPORT,		// 3
	UNSET,		// 4
	ENV,		// 5
	EXIT,		// 6
	N_BUILTINS
}	t_built_ins;

typedef enum e_in_type
{
	F_IN,
	F_HEREDOC
}	t_in_type;

typedef enum e_out_type
{
	F_OUT,
	F_APPEND
}	t_out_type;


typedef struct s_infile
{
	char		*filename_delim;
	int			fd;
	t_in_type	type;		
}	t_infile;

typedef struct s_outfile
{
	char		*filename;
	t_out_type	type;		
}	t_outfile;

typedef struct s_redir
{

	int			n_in;
	t_infile	infiles[MAX_FILES];		// list of infiles
	int			n_out;
	t_outfile	outfiles[MAX_FILES];		// list of outfiles
}	t_redir;

typedef struct s_cmdnode
{
	char	*cmd;		// one command
	int		argc;		// num of args
	char	*argv[MAX_ARGS];		// list of args
	t_redir	redir;
}	t_cmdnode;

typedef void (*FP) (t_cmdnode node, char *env[]);

#endif
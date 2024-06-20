/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:57:31 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/13 14:18:25 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	char		*filename;
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
	t_infile	*infiles;		// list of infiles
	int 		n_out;
	t_outfile	*outfiles;		// list of outfiles
}	t_redir;

typedef struct s_node
{
	char 	*cmd;		// one command
	int 	argc;		// num of args
	char	**argv;		// list of args
	t_redir	redir;
}	t_node;


//UTILS
void	my_exit(char *msg);
char	*find_path(char *cmd, char *env[]);
void	printerr_cur_cmd(char *cmd);
void	close_and_dup(int pipefd[], int is_child);

//PIPEX
void	my_exec(char *cmd, char *env[]);
void	my_piped_exec(char *cmd, char *env[]);
void	my_pipex(t_files files, char *cmds[], char *envp[]);
int		main(int argc, char *argv[], char *envp[]);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:57:31 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/16 18:49:56 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../2_structs/structs.h"
# include "../4_builtin/builtin.h"
//#include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

//UTILS
int		check_builtin(t_cmdnode node);
int		exec_builtin(t_cmdnode node, t_shcontext *env);
char	*find_path(char *cmd, char *env[]);
void	printerr_cur_cmd(char *cmd);
void	close_and_dup(int pipefd[], int is_child);
int		here_doc(char *delimiter, t_shcontext *env);
int		solve_path(t_cmdnode *node, char *env[], int *status);
void	expand_heredoc(char **line, t_shcontext *env);
int		process_heredocs(int n_nodes, t_cmdnode *nodes, t_shcontext *env);
int		process_infiles(int n, t_infile	*infiles);
int		process_outfiles(int n, t_outfile *outfiles);
int		here_doc(char *delimiter, t_shcontext *env);
int		get_real_exit_status(int status);

//PIPEX
void	run_exec(int n_nodes, t_cmdnode nodes[], t_shcontext *env);

#endif
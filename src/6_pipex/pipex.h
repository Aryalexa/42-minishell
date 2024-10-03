/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:57:31 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 16:09:19 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../1_libft/libft.h"
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
int     expand_dollar_simplehd(char *code, int *i, char **val);
int		here_doc(char *delimiter, t_shcontext *env);
int		solve_path(t_cmdnode *node, char *env[], int *status);
int		read_line(char **line);
void	expand_heredoc(char **line, t_shcontext *env);
int		process_heredocs(int n_nodes, t_cmdnode *nodes, t_shcontext *env);
int		here_doc(char *delimiter, t_shcontext *env);
int		get_signal_status(int status);
//PIPEX
void	run_exec(int n_nodes, t_cmdnode nodes[], t_shcontext *env);

#endif
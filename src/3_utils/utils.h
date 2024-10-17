/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:45:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/17 16:16:35 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../2_structs/structs.h"
# include <sys/ioctl.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

void	my_perror_exit(char *msg);
void	my_perror_exit_st(char *msg, int err);
void	my_perror(char *msg);
void	my_perr_arg(char *msg, char *var_name);
void	my_perr_arg_exit(char *msg, char *var_name);
void	*my_malloc(size_t size);
void	*my_calloc(size_t count, size_t size);
int		isreserved(char c);
int		isreservedall(char c);
int		isquote(char c);
void	debug(char *msg);
void	debug_int(char *fdname, int fdint);
void	debug_str(char *name_desc, char *str);
void	debug_env(t_shcontext *env);
void	swap_and_free_strings(char **s1, char **s2);
void	free_node(t_cmdnode node);
void	free_nodes(int n_nodes, t_cmdnode *nodes);
void	signal_main(void);
void	signal_father(void);
void	signal_child(void);
void	signal_heredoc(void);
void	signal_ignore(void);

#endif
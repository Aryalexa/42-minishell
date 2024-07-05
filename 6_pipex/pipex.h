/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:57:31 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/05 19:25:29 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../1_libft/libft.h"
#include "../2_structs/structs.h"
#include "../4_builtin/builtin.h"
//#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//UTILS
void	my_exit(char *msg);
char	*find_path(char *cmd, char *env[]);
void	printerr_cur_cmd(char *cmd);
void	close_and_dup(int pipefd[], int is_child);
int 	here_doc(char *delimiter);

//PIPEX
void	my_pipex(int n_nodes, t_cmdnode nodes[], char *env[]);

#endif
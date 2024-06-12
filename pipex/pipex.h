/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:57:31 by msoriano          #+#    #+#             */
/*   Updated: 2024/06/12 21:31:22 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/*
typedef struct s_files
{
	int		fdin;
	char	**outfiles;
	char	**appoutfiles;
}	t_files;
*/
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:47 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 17:41:43 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../2_structs/structs.h"
# include "../3_utils/utils.h"

void	exec_echo(t_cmdnode node, char *env[]);
void	exec_exit(t_cmdnode node, char *env[]);
void	exec_cd(t_cmdnode node, char *env[]);
void	exec_env(t_cmdnode node, char *env[]);
void	exec_export(t_cmdnode node, char *env[]);
void	exec_unset(t_cmdnode node, char *env[]);
void	exec_pwd(t_cmdnode node, char *env[]);
void	expand_token_val(char **val);

#endif
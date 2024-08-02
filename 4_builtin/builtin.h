/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:47 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/02 14:07:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../2_structs/structs.h"
# include "../3_utils/utils.h"

void	exec_echo(t_cmdnode node, t_env env);
void	exec_exit(t_cmdnode node, t_env env);
void	exec_cd(t_cmdnode node, t_env env);
void	exec_env(t_cmdnode node, t_env env);
void	exec_export(t_cmdnode node, t_env env);
void	exec_unset(t_cmdnode node, t_env env);
void	exec_pwd(t_cmdnode node, t_env env);
char	*expand_token_val(char *code);
char	*get_pwd(char *env[]);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:47 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/05 19:11:43 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../2_structs/structs.h"
# include "../3_utils/utils.h"

# define PATH_MAX 1000

void	exec_echo(t_cmdnode node, t_env *env);
void	exec_exit(t_cmdnode node, t_env *env);
void	exec_cd(t_cmdnode node, t_env *env);
void	exec_env(t_cmdnode node, t_env *env);
void	exec_export(t_cmdnode node, t_env *env);
void	exec_unset(t_cmdnode node, t_env *env);
void	exec_pwd(t_cmdnode node, t_env *env);
char	*expand_token_val(char *code, t_env *env);
int     envvar_index(char *key_srch, t_env *env);
void	update_envvar(char *key, char *value, t_env *env);
void	get_kv(char *line, char **key, char **value);

#endif
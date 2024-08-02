/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:52:33 by msoriano          #+#    #+#             */
/*   Updated: 2024/08/02 14:05:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*checkpath(char	*path,  t_env env)
{
	char	*abs_path;
	int		i;

	if(path[0] == '/')
		abs_path = ft_strdup(path);
	else
	{
		//BUSCAR ORIGINAL Y COPIARLO	
		i = 0;
		while (ft_strnstr(env.envp[i], "PWD", 3) == NULL)
			i++;
		abs_path = ft_strdup(env.envp[i]);
//		abs_path = ft_strjoin(get_pwd(env.env), "/");
//		ft_strjoin_inplace(&abs_path, path);
	}
	if (access(path, F_OK) == 0)
		return (abs_path);
	return(NULL);
}

void	replace_envar(char *key, char *value, char *env[])
{
	int	i;
	char	*line;

	i = 0;
	while (ft_strnstr(env[i], key, ft_strlen(key)) == NULL)
		i++;
	line = ft_strjoin(key, value);
	free(env[i]);
	env[i] = line;
}


void	exec_cd(t_cmdnode node,  t_env env)
{
	char	*abs_path;
	
	if (node.argc > 2)
	{
		my_perror("Error. Too many arguments.");
		return;
	}
	abs_path = checkpath(node.argv[1], env);
	if(!abs_path)
	{
		my_perror("Error. No such file or directory.");
		return;
	}
	if(chdir(node.argv[1]) != 0)
	{
		my_perror("Error. Failed to change directory.");
		return;
	}
	replace_envar("PWD=", abs_path, env.env);
	free(abs_path);
}
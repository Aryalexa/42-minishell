/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:09 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/13 18:30:28 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		ft_strjoin_inplace(&paths[i], "/");
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_arrstr(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_free_arrstr(paths);
	return (NULL);
}

/**
 * return the number of builtin
 * return -1 if not builtin
 */
int	check_builtin(t_cmdnode node)
{
	int			i;
	const char	built_ins_names[7][7] = {"echo", "exit", "pwd",
		"export", "unset", "env", "cd"};

	if (!node.cmd)
		return (-1);
	i = 0;
	while (i < 7) // number of builtins
	{
		if (ft_strcmp(node.cmd, (char *)built_ins_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}



// void	printerr_cur_cmd(char *cmd)
// {
// 	write(2, "while executing ", 16);
// 	write(2, cmd, ft_strlen(cmd));
// 	write(2, "...\n", 4);
// }

void	close_and_dup(int pipefd[], int is_child)
{
	if (is_child == 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

int	read_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	write(1, "> ", 2);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	// buffer[i] = '\n';
	// buffer[++i] = '\0';
	buffer[i] = '\0';
	*line = buffer;
	//free(buffer);
	return (r);
}

int	expand_dollar_simplehd(char *code, int *i, char **val)
{
	if (!code[*i + 1] || !ft_isalnum(code[*i + 1]))
	{
		*val = ft_strdup("$");
		return (1);
	}
	return (0);
}

/**
 * substitute line with its expanded version.
 * It also saves a '\n' at the end
 * line "hola $USER at $HOME"
 * new_line "hola username ar home/username"
 */
void	expand_heredoc(char **line, t_shcontext *env)
{
	int		i;
	char	*new_line;
	char	*dollar_exp;
	int		j;

	i = 0;
	new_line = my_calloc(ft_strlen(*line) + 1, 1);
	j = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			j += expand_dollar_simplehd(*line, &i, &dollar_exp);
			j += expand_dollar(*line, &i, &dollar_exp, env);
			new_line = ft_strjoin_inplace(&new_line, dollar_exp);
			free(dollar_exp);
		}
		else
		{
			new_line = ft_strappendc_inplace(new_line, (*line)[i++]);
			j++;
		}
	}
	new_line = ft_strappendc_inplace(new_line, '\n');
	free(*line);
	*line = new_line;
}

int	here_doc(char *delimiter, t_shcontext *env)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (read_line(&line))
		{
			debug_str("line=", line);
			debug_int("str(line)=", ft_strlen(line));
			debug_str("delimeter=", delimiter);
			debug_int("str(delimiter)=", ft_strlen(delimiter));
			debug_int("compare", ft_strncmp(line, delimiter, 2));  //
			//line[ft_strlen(line) - 1] = '\0';
			if (ft_strncmp(line, delimiter, 2) == 0)
				exit(0);
			debug("BEFORE EXPAND HEREDOC");
			expand_heredoc(&line, env);
			debug("SALIO DEL EXPAND HEREDOC");
			debug_str("line", line);  //
			//line[ft_strlen(line) - 1] = '\n';
			
			write(pipe_fd[1], line, ft_strlen(line));
			//write(pipe_fd[1], "\n", 1);
			free(line);
		}
		return (0);
	}
	else
	{
		close(pipe_fd[1]);
		return (wait(NULL), pipe_fd[0]);
	}
}

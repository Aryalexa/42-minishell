/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:22:41 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 12:32:03 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../main/minishell.h"
#include "../libft/libft.h"



/* Función para comparar env y envp */
int compare_env(char **env, char **envp) 
{
    int i;

    i = 0;
    while (env[i] != NULL && envp[i] != NULL) 
    {
        if (strcmp(env[i], envp[i]) != 0) 
            return 0;
        i++;
    }
    return (env[i] == NULL && envp[i] == NULL);
}

char **create_env(char *envp2[])
{
    char	**env;
    int     size;

	size = 0;
	while (envp2[size] != NULL)
		size++;
	env = malloc((size + 1) *sizeof(char *));
	if (!env)
        return NULL;
	size = 0;
	while (envp2[size] != NULL)
	{
		env[size] = strdup(envp2[size]);
        if (env[size] == NULL)
            return NULL;
		size++;
	}
    env[size] = NULL;
    return(env);
}
/*Copies envp and checks its the same*/
int	main(int argc, char *argv[], char *envp[])
{
    char **env;
    
    env = create_env(envp);

    /* Comparar envs */
    if (compare_env(env, envp)) 
        printf("env y envp son iguales.\n");
    else
        printf("env y envp no son iguales.\n");
}
/*Begins minishell and checks the input*/
int main(int argc, char **argv)
{
    char *input;
    while(1)
    {
        input = readline("minishell> ");
        if (input) 
        {
            add_history(input);
        }
        //Ctrl+D and NULL management to exit program
        if (input == NULL) 
        {
            printf("\n");
            break;        
        }
        //We print the input back
        printf("Input: %s\n", input);
        //Free variable input
        free(input);
    }
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:22:41 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 15:32:14 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Begins minishell and checks the input
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
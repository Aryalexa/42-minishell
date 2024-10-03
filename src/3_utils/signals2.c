/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:11:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 21:49:13 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * signal handler.
 * RL config:
 * - make "\n" the input
 * - make rl start in new line
 * - replace the input for ""
 * Exit status:
 * - exit with 130 
 */
void	handler_heredoc(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}

// void	hndlr_padre(int signum)
// {
// 	(void)signum;
// 	ft_putstr_fd("recibido padre\n", 2);
// }

// void	hndlr_hijo(int signum)
// {
// 	(void)signum;
// 	ft_putstr_fd("recibido hijo\n", 2);
// }

//signal(SIGQUIT, hndlr_hijo);
void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_heredoc);
}

//signal(SIGQUIT, hndlr_padre);
void	signal_ignore(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

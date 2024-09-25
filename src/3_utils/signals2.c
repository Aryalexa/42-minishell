/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:11:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/25 16:44:49 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


void	handler_heredoc(int signum)
{
	(void)signum;
	ft_printf("---\n");
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
	exit(0);
}

void	hndlr_padre(int signum)
{
	(void)signum;
	ft_putstr_fd("recibido padre\n", 2);
}

void	hndlr_hijo(int signum)
{
	(void)signum;
	ft_putstr_fd("recibido hijo\n", 2);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, hndlr_hijo);
	signal(SIGINT, handler_heredoc);

}

void	signal_ignore(void)
{
	signal(SIGQUIT, hndlr_padre);
	signal(SIGINT, SIG_IGN);
}


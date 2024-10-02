/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:11:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/02 14:27:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


void	handler_heredoc(int signum)
{
	(void)signum;
	// ft_printf("\n");
	ioctl(0, TIOCSTI, "\n");
	// debug("g_sigintsrc = 1");
	// g_sigintsrc = 1;
	exit(130);
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
	//signal(SIGQUIT, hndlr_hijo);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_heredoc);

}

void	signal_ignore(void)
{
	//signal(SIGQUIT, hndlr_padre);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:11:18 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/03 13:25:10 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// debug("g_sigintsrc = 1");
// g_sigintsrc = 1;

void	handler_heredoc(int signum)
{
	(void)signum;
	ioctl(0, TIOCSTI, "\n");
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

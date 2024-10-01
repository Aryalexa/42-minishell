/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:10 by msoriano          #+#    #+#             */
/*   Updated: 2024/10/01 21:29:50 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	my_handler_c(int signum)
{
	(void)signum;
	//exit_status = 130; !!
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// debug("g_sigintsrc = 1");
	// g_sigintsrc = 1;
}

void	my_handler_father(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	else
		ft_printf("Quit (core dumped)\n");
}

void	signal_main(void)
{
	signal(SIGINT, my_handler_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_father(void)
{
	signal(SIGQUIT, my_handler_father);
	signal(SIGINT, my_handler_father);
}


void	signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, my_handler_c);
}


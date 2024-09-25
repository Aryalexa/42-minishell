/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:48:10 by msoriano          #+#    #+#             */
/*   Updated: 2024/09/25 16:34:12 by macastro         ###   ########.fr       */
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
}

void	my_handler_father(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	else
	// 131
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


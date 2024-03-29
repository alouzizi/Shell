/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:50:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/16 14:17:23 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctl_c(int signum)
{
	if (signum == SIGINT && !g_global.signal && !g_global.is_child)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 1;
	}
	else if (signum == SIGINT && !g_global.signal && g_global.is_child == 1)
		g_global.signal = 1;
	else if (signum == SIGINT && g_global.signal)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 130;
		g_global.signal = 0;
	}
}

void	sig_quit(int signum)
{
	if (signum == SIGQUIT && g_global.signal)
	{
		ft_putendl_fd("Quit: 3", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 131;
	}
	else if (signum == SIGQUIT && !g_global.signal && g_global.is_child == 1)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_global.status = 131;
	}
	else if (signum == SIGQUIT && !g_global.signal)
		signal(SIGQUIT, SIG_IGN);
}

void	signals_handling(void)
{
	signal(SIGINT, &ctl_c);
	signal(SIGQUIT, &sig_quit);
	rl_catch_signals = 0;
}

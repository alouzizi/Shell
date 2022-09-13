/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:04:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/13 09:14:03 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_display(char **env)
{
	char	*s;

	while (1)
	{
		g_global.signal = 0;
		s = readline("minishell $ ");
		add_history(s);
		if (!s)
		{
			ft_putstr_fd(CTL_D, 1);
			exit (0);
		}
		if (!check_qouts(s))
			tree(s);
		else
		{
			g_global.status = 1;
			ft_putstr_fd("Syntax Error : Check Quotes!\n", 2);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1 || av[1])
		return (1);
	ft_update_env(env);
	signals_handling();
	prompt_display(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:04:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/22 01:56:03 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_display(t_vars *v)
{
	char	*s;

	while (1)
	{
		g_global.signal = 0;
		g_global.is_child = 0;
		s = readline("minishell $ ");
		if (ft_strlen(s))
			add_history(s);
		if (!s)
		{
			ft_putstr_fd(CTL_D, 1);
			exit (g_global.status);
		}
		if (!check_quotes(s, 0, 0))
			tree(s, v);
		else
		{
			g_global.status = 1;
			ft_putendl_fd("Syntax Error : Check Quotes!", 2);
		}
		free(s);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	v;

	if (ac != 1 || av[1])
		return (1);
	g_global.signal = 0;
	g_global.is_child = 0;
	g_global.status = 0;
	ft_update_env(env, &v);
	signals_handling();
	prompt_display(&v);
}

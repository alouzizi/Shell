/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:04:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/24 06:21:56 by ooumlil          ###   ########.fr       */
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
		if (!check_quotes(s, 0, 0))
			tree(s, env);
		else
		{
			g_global.status = 1;
			ft_putendl_fd("Syntax Error : Check Quotes!", 2);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char	**new_env;

	if (ac != 1 || av[1])
		return (1);
	new_env = ft_update_env(env);
	signals_handling();
	prompt_display(new_env);
}

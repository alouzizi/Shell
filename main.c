/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:04:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/17 20:21:50 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_display(void)
{
	t_tree	*root;
	char	*s;

	root = NULL;
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
		if (!check_quotes(s, -1, 0))
			tree(&root, s);
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
	if (ac != 1 || av[1])
		return (1);
	g_global.signal = 0;
	g_global.is_child = 0;
	g_global.status = 0;
	parse_env(env);
	signals_handling();
	prompt_display();
	return (0);
	}



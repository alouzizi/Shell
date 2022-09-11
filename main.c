/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:48:48 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/09 14:58:38 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    prompt_display(char **env)
{
	char	*s;

	while (1)
	{
		s = readline("minishell $ ");
		add_history(s);
		if (!s)
		{
			ft_putstr_fd(CTL_D, 1);
			exit (0);
		}
		if (!check_qouts(s))
			printf("Syntax ok\n"); // add fct store cmd
		else
		{
			ft_putstr_fd("Syntax Error : Check Quotes!\n", 2);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1 || av[1])
		return (1);
	prompt_display(env);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:20:45 by matef             #+#    #+#             */
/*   Updated: 2022/12/16 14:21:36 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exit_2(char *str)
{
	if (is_number(str))
	{
		printf("exit\n");
		g_global.status = ft_atoi(str);
		exit (g_global.status);
	}
	printf("exit\nbash: exit: : %s: numeric argument required\n", str);
	g_global.status = 255;
	exit (255);
}

int	is_number(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!(nbr[i] >= '0' && nbr[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_arg(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	if (i > 2)
	{
		if (!is_number(ptr[1]))
		{
			printf("exit\nbash: exit: : %s: numeric argument required\n", ptr[1]);
			g_global.status = 255;
			exit (255);
		}
		printf("exit\nbash: exit: too many arguments\n");
		g_global.status = 255;
		return (0);
	}
	else
	{
		if (ptr[1])
			ft_exit_2(ptr[1]);
		printf("exit\n");
		exit (0);
	}
	return (1);
}

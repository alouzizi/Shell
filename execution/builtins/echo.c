/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:07:18 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/17 19:24:20 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo(char **av, int i, int n)
{
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[++i])
			printf(" ");
	}
	if (n == 1)
		printf("\n");
}

void	echo(char **av)
{
	int	i;
	int	n;
	int	j;

	i = 1;
	n = 1;
	while (av[i] && !ft_strncmp(av[i], "-n", 2))
	{
		if (av[i][2] != '\0')
		{
			j = 2;
			while (av[i][j] == 'n')
				j++;
			if (av[i][j] && av[i][j] != 'n')
			{
				printf("%s", av[i]);
				return ;
			}
		}
		n = 0;
		i++;
	}
	print_echo(av, i, n);
}

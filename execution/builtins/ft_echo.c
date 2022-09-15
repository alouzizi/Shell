/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:40:19 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 02:00:47 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// check_n to check for "-n" and skip it as long as
// it exists, cz in the echo cmd usually in the end it
// adds a new line, if the flag "-n" is used it removes
// the new line in the end of line

int	check_n(char *cmd)
{
	int	i;

	if (!cmd)
		return (1);
	i = 0;
	if (cmd[i] == '-')
	{
		i++;
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

// ft_echo executes the same behavior as echo cmd,
// here we are told to handle the "-n" flag only
// ft_echo writes to STDOUT the input the user enters.
// with arguments separated by a space " "  

void	ft_echo(char **cmd)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (!cmd[1])
		return (ft_putstr_fd("\n", 1));
	while (cmd[i] && !check_n(cmd[i]))
	{
		if (cmd[i][1] != 'n')
			break ;
		check = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] && cmd[i][0])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!check)
		ft_putstr_fd("\n", 1);
	g_global.status = 0;
}

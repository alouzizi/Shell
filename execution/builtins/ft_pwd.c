/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:40:13 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/20 22:36:34 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// ft_pwd prints the current working directory
// getcwd gets the cwd and stores it in s

void	ft_pwd(void)
{
	char	s[1024];

	getcwd(s, sizeof(s));
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	g_global.status = 0;
}

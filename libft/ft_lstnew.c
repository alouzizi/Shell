/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 03:09:55 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/26 03:29:34 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(char *content)
{
	t_node	*s;

	s = (t_node *)malloc(sizeof(*s));
	if (!s)
		return (NULL);
	s -> s = content;
	s -> next = NULL;
	return (s);
}

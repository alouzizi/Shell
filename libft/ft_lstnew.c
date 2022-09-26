/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 03:09:55 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/26 03:10:23 by alouzizi         ###   ########.fr       */
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
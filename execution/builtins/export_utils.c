/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:55:00 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/17 01:55:44 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_back(t_env **lst, t_env *new)
{
	t_env	*last;
	t_env	*temp;

	temp = *lst;
	if (temp)
	{
		last = last_node(temp);
		last->next = new;
	}
	else
		*lst = new;
}

int	ony_chars(char c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_');
}

t_env	*last_node(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

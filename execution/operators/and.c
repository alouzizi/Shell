/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:07 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 22:37:44 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	simple_cmd(t_tree *root)
{
	return (execute(root->s));
}

int	and_operator(t_tree *root)
{
	if (!simple_cmd(root->left))
		simple_cmd(root->right);
	return (0);
}

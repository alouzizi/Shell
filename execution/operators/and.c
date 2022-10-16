/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:07 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 09:03:50 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	simple_cmd(t_tree *root, t_vars *v)
{
	return (execute(root->s, v));
}

int	and_operator(t_tree *root, t_vars *v)
{
	if (!simple_cmd(root->left, v))
		simple_cmd(root->right, v);
	return (0);
}

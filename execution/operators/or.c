/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:14:59 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/21 04:37:25 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	operator_selection(t_tree *root, t_vars *v)
{
	if (!builtincmp(root->s[0], "|"))
		return (create_pipe(root, v));
	else if (!builtincmp(root->s[0], "||"))
		return (or_operator(root, v));
	else if (!builtincmp(root->s[0], "&&"))
		return (and_operator(root, v));
	else if (!builtincmp(root->s[0], ">"))
		return (redirecte_output(root, 0, v));
	else if (!builtincmp(root->s[0], "<"))
		return (redirect_intput(root, v));
	else if (!builtincmp(root->s[0], ">>"))
		return (redirecte_output(root, 1, v));
	else
		return (simple_cmd(root, v));
	return (0);
}

int	or_operator(t_tree *root, t_vars *v)
{
	if (simple_cmd(root->left, v))
		simple_cmd(root->right, v);
	return (0);
}

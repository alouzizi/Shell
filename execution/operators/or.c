/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:14:59 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/16 14:44:54 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	operator_selection(t_tree *root)
{
	if (!builtincmp(root->s[0], "|"))
		return (create_pipe(root));
	else if (!builtincmp(root->s[0], ">"))
		return (redirecte_output(root, 0));
	else if (!builtincmp(root->s[0], "<"))
		return (redirect_intput(root));
	else if (!builtincmp(root->s[0], ">>"))
		return (redirecte_output(root, 1));
	else if (!builtincmp(root->s[0], "<<"))
		return (redirect_intput(root));
	else
		return (simple_cmd(root));
	return (0);
}
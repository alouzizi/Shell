/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:11:44 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 14:59:55 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_data
{
	int		signal;
	int		status;
	int		is_child;
	char	**n_env;
}	t_data;

typedef struct tree
{
	struct tree	*right;
	struct tree	*left;
	char		**s;
}	t_tree;

typedef struct redirct
{
	char	**param;
	char	**file;
	int		j;
}t_redirct;

#endif
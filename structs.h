/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:11:44 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/18 22:38:14 by ooumlil          ###   ########.fr       */
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
}	t_redirct;

typedef struct s_vars
{
	int		i;
	int 	j;
	int		l;
	char	**env;
}	t_vars;

typedef struct s_exp
{
	int	i;
	int	j;
	int	b;
	int	index;
	int	check;
	int	ptr;
}	t_exp;

#endif

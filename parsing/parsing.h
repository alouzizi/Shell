/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:06:36 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 22:36:19 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef struct tree
{
	struct tree	*right;
	struct tree	*left;
	char		**s;
}	t_tree;

void	print_tree(t_tree *root, int space);
void	tree(char *s, char **env);
t_tree	*newtree(char **content);
char	*data(int j, char c, char c2);
void	signals_handling(void);
t_node	*get_cmd(char *s, int *l);
int		check_quotes(char *s, int i, int j);
int		normall_collect(t_node **cmd, char *s, int *i);
void	handle_quotes(t_node **cmd, char *s, char c, int *i);
t_node	*create_node(char *str, int start, int end);
char	**transfer_list_to_2darray(t_node *node);

#endif
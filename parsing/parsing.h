/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:06:36 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 22:57:51 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

void		print_tree(t_tree *root, int space);
char		*data(int j, char c, char c2);
t_tree		*newtree(char **content);
void		tree(char *s, t_vars *v);
t_node		*get_cmd(char *s, int *l, t_vars *v);
int			check_quotes(char *s, int i, int j);
int			normall_collect(t_node **cmd, char *s, int *i, t_vars *v);
void		handle_quotes(t_node **cmd, char *s, char c, int *i, t_vars *v);
t_node		*create_node(char *str, int start, int end);
char		**transfer_list_to_2darray(t_node *node);
char		*expand_dollar(char *s, int start, int lvl, char c, t_vars *v);
char		*expand_dollar_2(char *s, int i, t_vars *v);
void		signals_handling(void);
t_redirct	*redirection_parse(t_tree *root, char *str, int *i, t_vars *v);
char		**ft_strjoin2d(char **s, char **s0);
int			pipe_parsing(t_tree **root, char **str, char *s, int j);
int			redirection(t_tree **temp, char *s, char **str, int j, t_vars *v);
void		open_heredoc(t_tree *root);
void		check_heredoc(t_tree *root);
void		free_tree(t_tree *root);

#endif
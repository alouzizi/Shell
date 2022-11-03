/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:06:36 by ooumlil           #+#    #+#             */
/*   Updated: 2022/11/03 01:00:43 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

void		print_tree(t_tree *root, int space);
char		*data(int j, char c, char c2);
t_tree		*newtree(char **content);
void		tree(t_tree **root, char *s, t_vars *v);
t_node		*get_cmd(char *s, int *l, t_vars *v);
int			check_quotes(char *s, int i, int j);
int			normall_collect(t_node **cmd, char *s, int *i, t_vars *v);
void		handle_quotes(t_node **cmd, char *s, int *i, t_vars *v);
t_node		*create_node(char *str, int start, int end);
char		**transfer_list_to_2darray(t_node *node);
char		*expand_dollar(char *s, int lvl, char c, t_vars *v);
char		*expand_dollar_2(char *s, int i, t_vars *v, char c);
void		signals_handling(void);
t_redirct	*redirection_pars(t_tree *temp, char *s, int *i, t_vars *v);
char		**ft_strjoin2d(char **s, char **s0);
int			pipe_parsing(t_tree **root, char **str, char *s, int j);
t_redirct	*redirection(t_tree **temp, char *s, char **str, t_vars *v);
void		free_tree(t_tree *root);
int			get_redirect_file(t_redirct *p, char *str, int i);
void		check_herdocintree(t_tree **root);
void		herdoc(t_tree **root);
char		*ft_strjoin2(char *s1, char *s2, int i);
int			token_redirection(t_tree *temp, char *s);
int			token_file_param(t_tree **temp, char *s, t_redirct *r, t_vars *v);
int			check_nextredirect(t_tree *temp, char *s, t_redirct *p, t_vars *v);
void		what_next(t_node *node, char *s, int *i, t_vars *v);
char		*check_expand(char *s, int *i, char *dollar, t_vars *v);
int			print_error(char *s);
int			redirection_dup(t_tree *root, int o, int f, t_vars *v);
int			next(t_node *node, char *s, int star, t_vars *v);
char		**tabdup(char **tab);
void		free_redirect(t_redirct *p);
int			red(t_tree **root, char *s, char **str, t_vars *v);
#endif

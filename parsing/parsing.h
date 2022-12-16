/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:06:36 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/16 14:37:45 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void		print_tree(t_tree *root, int space);
char		*data(int j, char c, char c2);
void		tree(t_tree **root, char *s);
int			check_quotes(char *s, int i, int j);
void		handle_quotes(t_node **cmd, char *s, int *i);
t_node		*create_node(char *str, int start, int end);
char		**transfer_list_to_2darray(t_node *node);
char		*expand_dollar(char *s, int lvl, char c);
char		*expand_dollar_2(char *s, int i, char c);
void		signals_handling(void);
char		**ft_strjoin2d(char **s, char **s0);
int			pipe_parsing(t_tree **root, char **str, char *s, int j);
void		free_tree(t_tree *root);
int			get_redirect_file(t_redirct *p, char *str, int i);
void		check_herdocintree(t_tree **root);
void		herdoc(t_tree **root);
char		*ft_strjoin2(char *s1, char *s2, int i);
int			token_redirection(t_tree *temp, char *s);
int			token_file_param(t_tree **temp, char *s, t_redirct *r);
int			check_nextredirect(t_tree *temp, char *s, t_redirct *p);
void    	what_next(t_node *node, char *s, int *i);
char		*check_expand(char *s, int *i);
int			print_error(char *s);
int			redirection_dup(t_tree *root, int o, int f);
int			next(t_node *node, char *s);
char		**tabdup(char **tab);
void		free_redirect(t_redirct *p);
int			red(t_tree **root, char *s, char **str);

char	*get_value_from_env(char *str);
void	free_array(char **arr);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:49:44 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 02:49:44 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# define CTL_D "\033[A\033[12Cexit\n"
# define COUNT 10
# include "libft/libft.h"
# define CNF ": command not found"
# define PRMPT_ERR "minishell: "

typedef struct redirct
{
	char	**param;
	char	**file;
	int		j;
}	t_redirct;

typedef struct s_vars
{
	int		i;
	int		j;
	int		l;
	int		check;
	char	*tmp;
	char	*s;
	int		t;
	char	**env;
}	t_vars;

typedef struct s_exp
{
	int		i;
	int		j;
	int		b;
	int		index;
	int		check;
	int		ptr;
	char	*var_name;
	char	*arg_name;
	char	*arg_value;
}	t_exp;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct tree
{
	struct tree	*right;
	struct tree	*left;
	char		**s;
}	t_tree;

typedef struct s_data
{
	int		signal;
	int		status;
	int		is_child;
	int		b;
	t_env	*g_env;
	char	*user;
}	t_data;

typedef struct export_shit
{
	int						i;
	int						j;
	char					*key;
	char					*v;
}	t_export_shit;

t_env			*new_node2(char *key, char *value);
t_env			*last_node(t_env *lst);
t_tree			*newtree(char **content);
t_redirct		*redirection_pars(t_tree *temp, char *s, int *i);
t_redirct		*redirection(t_tree **temp, char *s, char **stprint);
t_data			g_global;
// pipe
void			dup_function(int fd1, int fd2, int i);
void			execute_pipe(char **arr);
void			pipe_right(int *fd, t_tree *root);
void			pipe_left(int *fd, t_tree *root);
int				create_pipe(t_tree *root);

//executing
char			**get_path(char *s);
char			*check_access(char **paths, int i);
char			*check_absolute_path(char *s);
int				builtincmp(char *s1, char *s2);
int				isbuiltin(char **cmd);
int				execute(char **s);
int				commands_execution(char *path, char **cmd);
void			exit_status(int status);
void			print_cnf_error(char *cmd);
int				redirecte_output(t_tree *root, int j);
int				redirect_intput(t_tree *root);

int				simple_cmd(t_tree *root);
int				operator_selection(t_tree *root);

void			parse_env(char **env);
int				make_env(char **env);
void			add_back(t_env **lst, t_env *new);
int				ony_chars(char c);
void			add_var_to_env(char *key, char *value);
char			*get_value_from_env(char *var);
void			print_tree(t_tree *root, int space);
char			*data(int j, char c, char c2);
void			tree(t_tree **root, char *s);
t_node			*get_cmd(char *s, int *l);
int				check_quotes(char *s, int i, int j);
int				normall_collect(t_node **cmd, char *s, int *i);
void			handle_quotes(t_node **cmd, char *s, int *i);
t_node			*create_node(char *str, int start, int end);
char			**transfer_list_to_2darray(t_node *node);
char			*expand_dollar(char *s, int lvl, char c);
char			*expand_dollar_2(char *s, int i, char c);
void			signals_handling(void);
char			**ft_strjoin2d(char **s, char **s0);
int				pipe_parsing(t_tree **root, char **str, char *s, int j);
void			free_tree(t_tree *root);
int				get_redirect_file(t_redirct *p, char *str, int i);
void			check_herdocintree(t_tree **root);
void			herdoc(t_tree **root);
char			*ft_strjoin2(char *s1, char *s2, int i);
int				token_redirection(t_tree *temp, char *s);
int				token_file_param(t_tree **temp, char *s, t_redirct *r);
int				check_nextredirect(t_tree *temp, char *s, t_redirct *p);
void			what_next(t_node *node, char *s, int *i);
char			*check_expand(char *s, int *i, int start, int j);
int				print_error(char *s);
int				redirection_dup(t_tree *root, int o, int f);
int				next(t_node *node, char *s);
char			**tabdup(char **tab);
void			free_redirect(t_redirct *p);
int				red(t_tree **root, char *s, char **str);

char			*get_value_from_env(char *str);
void			free_array(char **arr);

int				arr_len(char **arr);

void			pwd(void);
void			export(char **key_value);
void			cd(char *path);
void			unset(char **var);
void			echo(char **av);
void			print_env(void);
char			**new_env(void);
int				exitt(char **str);

int				open_herdoc(t_tree **root, char *s, int i, int o);
int				herdoc_loop(t_tree **root, int o, int i, char *her);
void			check_open_and_free(t_tree **root, int o, int i, char *her);
#endif
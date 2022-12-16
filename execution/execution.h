/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:29:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/16 14:27:03 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <errno.h>
# define CNF ": command not found"
# define PRMPT_ERR "minishell: "
typedef struct export_shit
{
	int						i;
	int						j;
	char					*key;
	char					*v;
}							t_export_shit;

// pipe
void				dup_function(int fd1, int fd2, int i);
void				execute_pipe(char **arr);
void				pipe_right(int *fd, t_tree *root);
void				pipe_left(int *fd, t_tree *root);
int					create_pipe(t_tree *root);

//executing
// char				**get_path(char *s, t_vars *v);
char				*check_access(char **paths, int i);
char				*check_absolute_path(char *s);
int					builtincmp(char *s1, char *s2);
int					isbuiltin(char **cmd);
int					execute(char **s, t_vars *v);
int					commands_execution(char *path, char **cmd, t_vars *v);
void				exit_status(int status);
void				print_cnf_error(char *cmd);

int					redirecte_output(t_tree *root, int j);
int					redirect_intput(t_tree *root, t_vars *v);

int					simple_cmd(t_tree *root, t_vars *v);
int					operator_selection(t_tree *root);

void				parse_env(char **env);
int					make_env(char **env);
void	add_back(t_env **lst, t_env *new);
int		ony_chars(char c);
// t_env	*last_node(t_env *lst);
void	add_var_to_env(char *key, char *value);
char	*get_value_from_env(char *var);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:29:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/14 12:48:43 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define CNF ": command not found"
# define PRMPT_ERR "minishell: "
# include "../minishell.h"

//pwd
void				ft_pwd(void);

//echo
void				ft_echo(char **cmd);

//env
void				shlvl_handling(int i);
void				ft_update_env(char **env);
void				ft_env(void);

//export
char				**ft_arr_copy(char **arr);
char				*ft_strjoin_no_free(char *s1, char const *s2);
int					check_arg_export(char *arg, int i);
int					arr_len(char **arr);
int					ft_isalnum_export(int c);
int					check_var_name(char *arg);
int					has_value(char *arg, int *ptr);
void				print_export_error(char *arg);
void				sort_array_alphabetically(char **arr, int i, int j);
void				add_var_to_env(char *var);
void				add_to_value(char *arg, int i, int ptr, int index);
void				update_or_add_var(int b, int ptr, char *var);
int					add_to_env(char *var, int b);
int					add_to_export(char *cmd);
int					add_variable(char *arg);
void				print_export(char **arr, int i, int j);
void				ft_export(char **cmd);

//unset
void				ft_unset(char **cmd);
void				free_array(char **arr);
int					remove_from_env(char *cmd);

//cd
void				ft_cd(char **cmd);
void				cd_error_printing(char *arg);
char				*get_env(char *str);

//exit
long long			a_to_ll(char *str);
void				ft_exit(char **cmd);

// pipe
void				dup_function(int *fd, int index);
void				execute_pipe(char **arr);
void				pipe_cmd_exec(t_tree *root, int index);
void				pipe_right(int *fd, t_tree *root);
void				pipe_left(int *fd, t_tree *root);
int					create_pipe(t_tree *root);

//executing
char				**get_path(char *s);
char				*check_access(char	**paths);
int					builtincmp(char *s1, char *s2);
int					isbuiltin(char **cmd);
int					execute(char **s);
int					commands_execution(char **paths, char **cmd);
void				exit_status(int status);
void				print_cnf_error(char *cmd);

int					redirecte_output(t_tree *root, int j);
int					redirect_intput(t_tree *root);

int					or_operator(t_tree *root);
int					and_operator(t_tree *root);
int					simple_cmd(t_tree *root);

#endif
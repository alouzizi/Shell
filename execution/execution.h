/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:29:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 10:39:15 by ooumlil          ###   ########.fr       */
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
void				shlvl_handling(int i, char **arr);
char				**ft_update_env(char **env);
void				ft_env(char **env);

//export
char				**ft_arr_copy(char **arr);
int					check_arg_export(char *arg, int i, char **env);
int					arr_len(char **arr);
int					ft_isalnum_export(int c);
int					check_var_name(char *arg);
int					has_value(char *arg, int *ptr);
void				print_export_error(char *arg);
void				sort_array_alphabetically(char **arr, int i, int j);
void				add_var_to_env(char *var, char **env);
void				add_to_value(char *arg, int i, int ptr, int index, char **env);
void				update_or_add_var(int b, int ptr, char *var, char **env);
int					add_to_env(char *var, int b, char **env);
int					add_variable(char *arg, char **env);
int					add_to_export(char *cmd, char **env);
void				print_export(char **arr, int i, int j);
void				ft_export(char **cmd, char **env);

//unset
char				**copy_after_unset(char **copy, int i);
char				*get_name(char *s, int c);
void				ft_unset(char **cmd, char **env);
void				free_array(char **arr);
int					remove_from_env(char *cmd, char **env);

//cd
void				ft_cd(char **cmd, t_vars *v);
void				cd_error_printing(char *arg);
char				*get_env(char *str, t_vars *v);

//exit
long long			a_to_ll(char *str);
void				ft_exit(char **cmd);

// pipe
void				dup_function(int *fd, int index);
void				execute_pipe(char **arr, t_vars *v);
void				pipe_right(int *fd, t_tree *root, t_vars *v);
void				pipe_left(int *fd, t_tree *root, t_vars *v);
int					create_pipe(t_tree *root, t_vars *v);

//executing
char				*get_path(char *s, t_vars *v);
// char				*check_access(char	**paths);
int					builtincmp(char *s1, char *s2);
int					isbuiltin(char **cmd, t_vars *v);
int					execute(char **s, t_vars *v);
int					commands_execution(char *path, char **cmd, t_vars *v);
void				exit_status(int status);
void				print_cnf_error(char *cmd);

int					redirecte_output(t_tree *root, int j, t_vars *v);
int					redirect_intput(t_tree *root, t_vars *v);

int					or_operator(t_tree *root, t_vars *v);
int					and_operator(t_tree *root, t_vars *v);
int					simple_cmd(t_tree *root, t_vars *v);
int					operator_selection(t_tree *root, t_vars *v);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:29:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/25 05:39:52 by ooumlil          ###   ########.fr       */
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
void				shlvl_handling(char **env, int i);
char				**ft_update_env(char **env);
void				ft_env(char **env);

//export
char				**ft_arr_copy(char **arr);
char				*ft_strjoin_no_free(char *s1, char const *s2);
int					check_arg_export(char *arg, int i, char **env);
int					arr_len(char **arr);
int					ft_isalnum_export(int c);
int					check_var_name(char *arg);
int					has_value(char *arg, int *ptr);
void				print_export_error(char *arg);
void				sort_array_alphabetically(char **arr);
void				add_var_to_env(char *var, char **env);
void				add_to_value(char *arg, char **env, int i, int ptr);
void				update_or_add_var(int b, int ptr, char *var, char **env);
void				add_to_env(char *var, char **env, int b);
void				add_variable(char *arg, char **env);
void				add_to_export(char **env, char *cmd);
void				sort_array_alphabetically(char **arr);
void				print_export(char **arr);
void				ft_export(char **cmd, char **env);

//unset
void				ft_unset(char **cmd, char **env);
void				remove_from_env(char *cmd, char **env);

//cd
void				ft_cd(char **cmd, char **env);
char				*get_env(char *str, char **env);

//exit
unsigned long long	a_to_ull(char *str);
void				ft_exit(char **cmd);

//pipe
// void				pipe_right(int *fd, t_tree *root, char **env);
// void				pipe_left(int *fd, t_tree *root, char **env);
// int					creat_pipe(t_tree *root, char **env);

//executing
char				**get_path(char *s, char **env);
int					builtincmp(char *s1, char *s2);
int					isbuiltin(char **cmd, char **env);
void				print_cnf_error(char *cmd);
void				execute(char **s, char **env);
void				commands_execution(char **paths, char **cmd, char **env);
char				*check_access(char	**paths);

#endif
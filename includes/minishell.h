/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/23 14:15:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

/* init shell */
t_shell	*init_shell(char **env, bool first_init);
void	free_shell(t_shell *data, bool close_shell);

/* expander */
bool	expand_tokens(t_shell *data);
bool	char_vec_push(t_vector *vec, char c);
bool	expand_sq(t_token *token, size_t *i, t_vector *vec, t_shell *data);
bool	expand_dq(t_token *token, size_t *i, t_vector *vec, t_shell *data);
bool	expand_env(char *str, size_t *i, t_vector *vec, t_shell *data);

/* lexer */
bool	lexer(char *input, t_shell *data);
bool	make_string(char *str, size_t *i, t_vector *vec);
bool	check_quotes_parantheses(char *input);
bool	create_string(char *str, size_t *i, t_vector *vec);
bool	create_quote_string(char *str, size_t *i, t_vector *vec);
bool	create_paran_string(char *str, size_t *i, t_vector *vec);
bool	operator_split(t_shell *data);
char	**split(t_token *token);

/* parser */
bool	parser(t_shell *data);
bool	is_pipe(char *str);
bool	is_r_redirect(char *str);
bool	is_l_redirect(char *str);
bool	is_a_redirect(char *str);
bool	is_heredoc(char *str);
void	verify_token_vec(t_shell *data);
bool	check_tokens(t_shell *data);
bool	combine_tokens(t_vector *vec, size_t i, t_types type);
void	free_found(t_vector *found);
/* group */
bool	group_token_vec(t_shell *data);
bool	hdoc_found(t_group *group, size_t i, t_shell *data);
bool	hdoc_expand(char **str, t_shell *data);

/* executor */
bool	executor(t_shell *data);
bool	create_processes(t_shell *data);
void	exec_process(t_group *group, t_process type, t_shell *data);
void	dup_fd(t_group *group, t_process type);
void	check_cmd(t_group *group, t_process type, t_vector *env_vec);
void	exec_built_in(t_group *group, t_process type, t_shell *data);
void	exec_absolute_path(t_group *group, t_process type, t_vector *env_vec);
void	handle_redirects(t_group *group);
void	validate_redirects(t_group *group);
void	close_pipes(t_shell *data);

void	exec_special_builtin(t_group *group, t_shell *data);

/* exec_utils */
bool	is_builtin(char *str);
bool	is_special_builtin(char *str);
char	**combine_env(t_vector *env_vec);

/* built_in */
void	ft_exit(t_group *group, t_shell *data);
void	ft_cd(t_group *group, t_shell *data);
void	ft_export(t_group *group, t_shell *data);
void	ft_unset(t_group *group, t_shell *data);
void	ft_echo(t_group *group);
void	ft_pwd(void);
void	ft_env(t_vector *env_vec);
void	print_env_dec(t_vector *env, char *arg_2);
void	update_or_create_env(t_vector *env, char *key, char *value);
char	**ft_export_split(char *src, char delimter);
size_t	**return_sorted_arr(t_vector *env);
void	ft_free_size_t(size_t **arr, size_t len);
char	*string_handler(char *input);
void	write_err_cd(t_shell *data, size_t option, char *path, char *extra);
/* signals */
void	signal_main(int signal_num);
void	setup_hdoc_signals(void);
void	signal_hdoc(int signal_num);
void	setup_child_signals(void);
void	signal_child(int signal_num);

/* structs */
t_token	*create_token(char *value, t_types type);
void	clear_token(void *data);
t_token	*dup_token(t_token *input);
t_env	*create_env(char *key, char *value);
void	clear_env(void *data);
t_group	*create_group(void);
void	clear_group(void *data);
void	clear_fname(void *data);
t_exec	*create_exec(void);
void	clear_exec(t_exec **exec);
void	init_env(char **env, t_vector *env_vec);

/* general utils */
bool	compare_env_key(void *item, void *key);
void	exit_mini(char *str, int exit_code);
bool	set_err(t_exit type, char *msg, t_shell *data);
void	exec_err(char *str, t_exit type);
void	exec_err_extra(char *str, t_exit type);
void	write_err(t_shell *data);
void	write_err_extra(t_shell *data);
bool	rm_quotes(t_token *token, bool set_string);
bool	type_compare(size_t num_args, t_types type, ...);
bool	filter_operators(void *item);
// bool	out_of_scope(t_vector *found, t_shell *data);
bool	is_redirect(t_token *token);

/* debug */
void	print_vector(t_vector *vec, void (*printer)(void *, size_t));
void	print_token(void *data, size_t i);
char	*print_type(t_types type);
char	*type_symbol(t_types type);
void	print_env(void *data, size_t i);
void	print_group(t_shell *data);
void	p_group(t_group *group);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/10/07 22:31:59 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

/* init shell */
t_shell	*init_shell(char **env, bool first_init);
void	free_shell(t_shell *data, bool close_shell);

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
bool	is_encased_dq(char *str);
bool	is_encased_sq(char *str);
bool	is_encased_parentheses(char *str);
bool	is_pipe(char *str);
bool	is_r_redirect(char *str);
bool	is_l_redirect(char *str);
bool	is_a_redirect(char *str);
bool	is_heredoc(char *str);
bool	contains_env_var(char *str);
bool	is_or(char *str);
bool	is_and(char *str);
void	verify_token_vec(t_shell *data);
bool	check_tokens(t_shell *data);
bool	combine_tokens(t_vector *vec, size_t i, t_types type);
void	free_found(t_vector *found);
/* group */
bool	group_token_vec(t_shell *data);
bool	hdoc_found(t_group *group, size_t i, t_shell *data);

/* executor */
bool	executor(t_shell *data);
bool	create_processes(t_shell *data);
void	exec_process(t_group *group, t_process type);
void	dup_fd(t_group *group, t_process type);
void	check_cmd(t_group *group, t_process type);
void	exec_built_in(t_group *group, t_process type);
void	exec_absolut_path(t_group *group);
void	handle_redirects(t_group *group);
void	exec_absolute_path(t_group *group, t_process type);

void	exec_special_builtin(t_group *group);

/* exec_utils */
bool	is_builtin(char *str);
bool	is_special_builtin(char *str);
char	**combine_env(t_vector *env_vec);

/* built_in */
void	ft_exit(t_group *group);
void	ft_cd(t_group *group);
void	ft_export(t_group *group);
void	ft_unset(t_group *group);
void	ft_echo(t_group *group);
void	ft_pwd(t_group *group);
void	ft_env(t_group *group);

/* structs */
t_token	*create_token(char *value, t_types type);
void	clear_token(void *data);
t_token	*dup_token(t_token *input);
t_env	*create_env(char *key, char *value);
void	clear_env(void *data);
t_group	*create_group(t_shell *data);
void	clear_group(void *data);
void	clear_fname(void *data);
t_exec	*create_exec(void);
void	clear_exec(t_exec **exec);

/* general utils */
void	exit_mini(char *str, int exit_code);
bool	set_err(t_exit type, char *msg, t_shell *data);
void	exec_err(char *str, t_exit type);
void	write_err(t_shell *data);
bool	rm_quotes(t_token *token, bool set_string);
bool	type_compare(size_t num_args, t_types type, ...);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/13 18:00:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <unistd.h>

/*
	Lists
*/
t_token	*list_append(t_token *head, char *str, t_types type);
t_token	*list_insert(t_token *head, char *str, t_types type, size_t index);

#endif

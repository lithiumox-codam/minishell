/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 22:36:40 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 14:06:29 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

void	clear_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->value);
}

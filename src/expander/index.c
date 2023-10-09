/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 09:53:38 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/09 12:46:43 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	filter_env(void *item)
{
	t_token	*token;
	size_t	i;

	i = 0;
	token = (t_token *)item;
	while (token->value[i])
	{
		if (token->value[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

static bool	expand_question(t_token *token, t_shell *data)
{
	if (token->value[1] != '?')
		return (true);
	free(token->value);
	token->value = ft_itoa(g_signal.exit_status);
	if (token->value == NULL)
		return (set_err(MALLOC, NULL, data), false);
	token->type = STRING;
	return (true);
}

bool	expand(t_shell *data)
{
	t_vector	*found;
	t_token		*token;
	size_t		i;

	i = 0;
	found = vec_find(&data->token_vec, filter_env);
	if (found == NULL)
		return (true);
	while (i < found->length)
	{
		token = (t_token *)vec_get(&data->token_vec, i);
		if (!token)
			return (set_err(MALLOC, NULL, data), false);
		if (!expand_question(token, data))
			return (false);
		i++;
	}
	if (found)
	{
		vec_free(found);
		free(found);
	}
	return (true);
}

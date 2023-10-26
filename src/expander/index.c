/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 09:53:38 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/26 15:07:02 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	expand(t_token *token, t_shell *data)
{
	t_vector	expanded_string;
	size_t		i;

	if (!vec_init(&expanded_string, 10, sizeof(char), NULL))
		return (set_err(MALLOC, "expand", data));
	i = 0;
	while (token->value[i])
	{
		if (checkchar(token->value[i], "\'"))
			expand_sq(token, &i, &expanded_string, data);
		else if (checkchar(token->value[i], "\""))
			expand_dq(token, &i, &expanded_string, data);
		else if (checkchar(token->value[i], "$"))
			expand_env(token, &i, &expanded_string, data);
		else
		{
			vec_push(&expanded_string, &token->value[i]);
			i++;
		}
	}
	convert_vec_to_string(expanded_string, token);
	return (true);
}

bool	expander(t_shell *data)
{
	size_t	i;
	size_t	j;
	t_token	*token;

	while (i < (&data->token_vec)->length)
	{
		token = vec_get(&data->token_vec, i);
		j = 0;
		while (token->value[j])
		{
			if (checkchar(token->value[j], "\"\'$"))
			{
				if (!expand(token, data))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

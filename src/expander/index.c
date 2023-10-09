/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 09:53:38 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/09 09:55:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	filter_env(void *item)
{
	t_token	*token;

	token = (t_token *)item;
	while (*token->value)
	{
		if (*token->value == '$')
			return (true);
		token->value++;
	}
	return (false);
}

bool	expand(t_shell *data)
{
	t_vector	*found;
	size_t		i;

	i = 0;
	found = vec_find(&data->token_vec, filter_env);
	if (found == NULL)
		return (true);
	while (i < found->length)
	{
		print_t_found(vec_get(found, i), i);
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 11:12:20 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/20 13:38:05 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool contains_env_var(char *str)
{
	if (ft_strchr(str, '$'))
		return (true);
	return (false);
}

void parser(t_vector *vec)
{
	t_token *token;
	size_t i;

	i = 0;
	while (i < vec->lenght)
	{
		token = (t_token *)ft_vec_get(vec, i);
		if (token->type == 0)
		{
			if (is_encased_dq(token->value))
				token->type = 1;
			else if (is_encased_sq(token->value))
				token->type = 2;
			else if (contains_env_var(token->value))
				token->type = 3;
			printf("Token %zu: %s\n", i, token->value);
			printf("Type: %i\n", token->type);
		}
		i++;
	}
}

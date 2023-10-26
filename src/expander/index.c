/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 09:53:38 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/27 00:48:50 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief vec push exlusively for sizeof(char) vectors, does not free incoming data
*/
bool char_vec_push(t_vector *vec, char c)
{
	if (vec->length == vec->capacity)
		if (vec_resize(vec, vec->capacity * 2) == false)
			return (false);
	if (!ft_memcpy(vec->data + vec->length * vec->type_size, &c,
			vec->type_size))
		return (false);
	vec->length++;
	return (true);
}

/**
 * @brief Converts the vector to a string
 */
static bool	convert_vec_to_string(t_vector *vec, t_token *token, t_shell *data)
{
	if (!vec_resize(vec, vec->length + 1))
		return (set_err(MALLOC, "convert_vec_to_string", data));
	char_vec_push(vec, '\0');
	free(token->value);
	token->value = ft_strdup((char *)vec->data);
	vec_free(vec);
	return (true);
}

static bool	call_expander(t_token *token, size_t *i, t_vector *expanded_string,
		t_shell *data)
{
	if (token->value[(*i)] == '\'')
	{
		if (!expand_sq(token, i, expanded_string, data))
		{
			vec_free(expanded_string);
			return (false);
		}
	}
	else if (token->value[(*i)] == '\"')
	{
		if (!expand_dq(token, i, expanded_string, data))
		{
			vec_free(expanded_string);
			return (false);
		}
	}
	else if (token->value[(*i)] == '$')
	{
		if (!expand_env(token, i, expanded_string, data))
		{
			vec_free(expanded_string);
			return (false);
		}
	}
	return (true);
}

static bool	expand(t_token *token, t_shell *data)
{
	t_vector	expanded_string;
	size_t		i;

	if (!vec_init(&expanded_string, 10, sizeof(char), NULL))
		return (set_err(MALLOC, "expand", data));
	i = 0;
	while (token->value[i])
	{
		if (checkchar(token->value[i], "\"\'$"))
		{
			if (!call_expander(token, &i, &expanded_string, data))
				return (false);
		}
		else
		{
			if (!char_vec_push(&expanded_string, token->value[i]))
			{
				vec_free(&expanded_string);
				return (set_err(MALLOC, "expand", data));
			}
			i++;
		}
	}
	return (convert_vec_to_string(&expanded_string, token, data));
}

// static bool	expand(t_token *token, t_shell *data)
// {
// 	t_vector	expanded_string;
// 	size_t		i;
// 	char		c;

// 	if (!vec_init(&expanded_string, 10, sizeof(char), NULL))
// 		return (set_err(MALLOC, "expand", data));
// 	i = 0;
// 	i++;
// 	char_vec_push(&expanded_string, token->value[i]);
// 	i++;
// 	char_vec_push(&expanded_string, token->value[i]);
// 	i++;
// 	char_vec_push(&expanded_string, token->value[i]);
// 	c = '\0';
// 	char_vec_push(&expanded_string, c);
// 	printf("Token value check: %s\n", token->value);
// 	printf("Expanded string check: %s\n", (char *)expanded_string.data);
// 	free(token->value);
// 	token->value = ft_strdup((char *)expanded_string.data);
// 	vec_free(&expanded_string);
// 	printf("Token value check2: %s\n", token->value);
// 	return (true);
// }

bool	expander(t_shell *data)
{
	size_t	i;
	size_t	j;
	t_token	*token;

	i = 0;
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
				break ;
			}
			j++;
		}
		i++;
	}
	return (true);
}

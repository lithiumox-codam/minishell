/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 09:53:38 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/26 17:46:06 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_char(void *c)
{
	free(c);
}

/**
 * @brief Converts the vector to a string
 */
static bool	convert_vec_to_string(t_vector *vec, t_token *token)
{
	char	*str;
	char	*new_str;

	if (!vec_resize(vec, vec->length + 1))
		return (false);
	printf("str: %s\n", (char *)vec->data);
	str = (char *)vec->data;
	str[vec->length] = '\0';
	new_str = ft_strdup(str);
	if (!new_str)
		return (set_err(MALLOC, "convert_vec_to_string", NULL));
	free(token->value);
	token->value = new_str;
	return (true);
}

static bool	call_expander(t_token *token, size_t *i, t_vector expanded_string,
		t_shell *data)
{
	if (token->value[(*i)] == '\'')
	{
		if (!expand_sq(token, i, &expanded_string, data))
			return (false);
	}
	else if (token->value[(*i)] == '\"')
	{
		if (!expand_dq(token, i, &expanded_string, data))
			return (false);
	}
	else if (token->value[(*i)] == '$')
	{
		if (!expand_env(token, i, &expanded_string, data))
			return (false);
	}
	return (true);
}

static bool	expand(t_token *token, t_shell *data)
{
	t_vector	expanded_string;
	size_t		i;
	char		*c;

	if (!vec_init(&expanded_string, 10, sizeof(char), free_char))
		return (set_err(MALLOC, "expand", data));
	i = 0;
	while (token->value[i])
	{
		if (checkchar(token->value[i], "\"\'$"))
		{
			if (!call_expander(token, &i, expanded_string, data))
				return (false);
		}
		else
		{
			c = malloc(sizeof(char));
			*c = token->value[i];
			if (!vec_push(&expanded_string, c))
			{
				free(c);
				return (set_err(MALLOC, "expand", data));
			}
			i++;
		}
	}
	if (!convert_vec_to_string(&expanded_string, token))
		return (false);
	vec_free(&expanded_string);
	return (true);
}

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
			}
			j++;
		}
		i++;
	}
	return (true);
}

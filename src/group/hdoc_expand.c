/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hdoc_expand.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 22:03:02 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/17 16:19:52 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Converts the vector to a string
 */
static bool	str_vec_to_string(t_vector *vec, char **str, t_shell *data)
{
	if (!vec_resize(vec, vec->length + 1))
		return (set_err(MALLOC, "convert_vec_to_string", data));
	char_vec_push(vec, '\0');
	free(*str);
	*str = (char *)vec->data;
	return (true);
}

bool	hdoc_expand(char **str, t_shell *data)
{
	t_vector	vec;
	size_t		i;

	if (!vec_init(&vec, 10, sizeof(char), NULL))
		return (set_err(MALLOC, "hdoc_expand", data));
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (!expand_env(*str, &i, &vec, data))
				return (free(str), false);
		}
		else
		{
			if (!char_vec_push(&vec, (*str)[i]))
			{
				vec_free(&vec);
				return (free(*str), set_err(MALLOC, "hdoc_expand", data));
			}
			i++;
		}
	}
	return ((str_vec_to_string(&vec, str, data)));
}

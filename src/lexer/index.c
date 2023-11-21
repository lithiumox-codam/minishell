/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 11:55:20 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/03 14:46:50 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	build_redir_token(char *input, size_t *i, t_shell *data)
{
	char	*value;
	size_t	size;

	size = 1;
	if (input[(*i)] == input[(*i) + 1])
		size++;
	value = ft_substr(input, (*i), size);
	if (!value)
		return (set_err(MALLOC, "build_redir_token", data));
	if (!vec_push(&data->token_vec, (void *)create_token(value, 0)))
	{
		free(value);
		return (set_err(MALLOC, "build_redir_token", data));
	}
	(*i) += size;
	return (true);
}

static bool	build_pipe_token(char *input, size_t *i, t_shell *data)
{
	char	*value;

	if (input[(*i)] == input[(*i) + 1])
		return (set_err(OUT_OF_SCOPE, "||", data));
	value = malloc(sizeof(char) * 2);
	value[0] = '|';
	value[1] = '\0';
	if (!vec_push(&data->token_vec, (void *)create_token(value, 0)))
		return (set_err(MALLOC, "build_pipe_token", data));
	(*i)++;
	return (true);
}

static bool	check_quote_finish(char *input, size_t *i, t_shell *data)
{
	char	quote;

	quote = input[(*i)];
	(*i)++;
	while (input[(*i)] && input[(*i)] != quote)
		(*i)++;
	if (input[(*i)] == '\0')
		return (set_err(SYNTAX_MINI, (char[2]){quote, '\0'}, data));
	(*i)++;
	return (true);
}

static bool	build_string_token(char *input, size_t *i, t_shell *data)
{
	size_t	start;
	char	*value;

	start = (*i);
	while (input[(*i)] && !checkchar(input[(*i)], " \\()<>|;&"))
	{
		if (checkchar(input[(*i)], "\"\'"))
		{
			if (!check_quote_finish(input, i, data))
				return (false);
		}
		else
			(*i)++;
	}
	value = ft_substr(input, start, (*i) - start);
	if (!value)
		return (set_err(MALLOC, "build_string_token", data));
	if (!vec_push(&data->token_vec, (void *)create_token(value, 0)))
	{
		free(value);
		return (set_err(MALLOC, "build_string_token", data));
	}
	return (true);
}

/**
 * @brief Splits a string into token_vec
 *
 * @param input	The string to split
 * @param data	t_shell data, of which token_vec will be used
 */
bool	lexer(char *input, t_shell *data)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (checkchar(input[i], "\\()<>|;&"))
		{
			if (checkchar(input[i], "();\\&"))
			{
				return (set_err(OUT_OF_SCOPE, ((char[2]){input[i], '\0'}), data));
			}
			if (checkchar(input[i], "<>"))
				if (!build_redir_token(input, &i, data))
					return (false);
			if (checkchar(input[i], "|"))
				if (!build_pipe_token(input, &i, data))
					return (false);
		}
		else if (!build_string_token(input, &i, data))
			return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:06:18 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/21 02:29:27 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	find_operator(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] && !checkchar(token->value[i], "<>|&"))
		i++;
	if (token->value[i] == '\0')
		return (false);
	return (true);
}

static bool	insert_array(t_shell *data, char **array, size_t *i)
{
	size_t	j;
	t_token	*token;

	j = 0;
	while (array[j])
	{
		token = create_token(array[j], UNKNOWN);
		if (!token)
		{
			ft_free(array);
			return (set_err(MALLOC, "insert_array", data));
		}
		if (!vec_insert(&data->token_vec, (*i) + j, token))
		{
			ft_free(array);
			return (set_err(MALLOC, "insert_array", data));
		}
		j++;
	}
	(*i) += j;
	return (true);
}

static bool	token_swap(t_shell *data, char **array, size_t *i)
{
	if (!vec_remove(&data->token_vec, (*i)))
	{
		ft_free(array);
		return (set_err(MALLOC, "token_swap", data));
	}
	if (!insert_array(data, array, i))
		return (false);
	return (true);
}

bool	operator_split(t_shell *data)
{
	size_t	i;
	t_token	*token;
	char	**array;

	i = 0;
	while (i < (&data->token_vec)->length)
	{
		token = (t_token *)vec_get(&data->token_vec, i);
		if (token->type == STRING && find_operator(token))
		{
			array = split(token);
			if (!array)
				return (set_err(MALLOC, "split", data));
			if (!token_swap(data, array, &i))
				return (false);
			free(array);
		}
		else
			i++;
	}
	return (parser(data));
}

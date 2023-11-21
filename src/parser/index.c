/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 11:12:20 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/21 13:39:14 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief A cheeky way to return a struct with a function pointer and a type
 *
 * @return t_func_map* A pointer to a t_func_map struct
 * @note The last element of the array is a struct with a NULL function pointer
 * and a type of 0 so the parser knows when to stop looping over the array
 */
t_func_map	*return_map(void)
{
	t_func_map	*func_map;

	func_map = (t_func_map *)malloc(sizeof(t_func_map) * 6);
	if (func_map == NULL)
		return (NULL);
	func_map[0] = (t_func_map){is_pipe, PIPE};
	func_map[1] = (t_func_map){is_r_redirect, O_REDIRECT};
	func_map[2] = (t_func_map){is_l_redirect, I_REDIRECT};
	func_map[3] = (t_func_map){is_a_redirect, A_REDIRECT};
	func_map[4] = (t_func_map){is_heredoc, HEREDOC};
	func_map[5] = (t_func_map){NULL, STRING};
	return (func_map);
}

/**
 * @brief Loops over the token_vec in the vector and parses them
 *
 * @param vec The vector containing the token_vec
 * @param func_map The array of structs with function pointers and types
 */
void	parse_loop(t_vector *vec, t_func_map *func_map)
{
	t_token	*token;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < vec->length)
	{
		token = (t_token *)vec_get(vec, i);
		if (token->type == UNKNOWN)
		{
			j = 0;
			while (func_map[j].func != NULL)
			{
				if (!func_map[j].func(token->value))
					j++;
				else
					break ;
			}
			token->type = func_map[j].type;
		}
		i++;
	}
}

/**
 * @brief Parses the token_vec in the vector
 *
 * @note The parser will only parse token_vec that have the type 0 so make sure
 * to set the type of the token_vec to 0 before calling this function
 * @param vec The vector containing the token_vec
 */
bool	parser(t_shell *data)
{
	t_func_map	*func_map;

	func_map = return_map();
	if (func_map == NULL)
	{
		free(func_map);
		return (set_err(MALLOC, "parser", data));
	}
	parse_loop(&data->token_vec, func_map);
	free(func_map);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 22:15:51 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/26 14:19:40 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Combines two strings with a space in between
 *
 * @param s1 The first string
 * @param s2 The second string
 * @return char* The combined string
 */
static char	*ft_strjoin_space(char *s1, char *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len == 0)
		return (ft_strdup(s2));
	if (s2_len == 0)
		return (ft_strdup(s1));
	ptr = malloc((s1_len + s2_len + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ft_memcpy(ptr, " ", 1);
	ft_memcpy(ptr + s1_len + 1, s2, s2_len);
	ptr[s1_len + s2_len + 2] = '\0';
	return (ptr);
}

/**
 * @brief Combines the given and next token into one token
 *
 * @param vec The vector to combine in of tokens
 * @param i The index of the first token
 * @return t_token* The combined token
 */
static t_token	*combine_tokens(t_vector *vec, size_t i)
{
	t_token	*first_token;
	t_token	*second_token;
	char	*result;
	t_token	*combined;

	first_token = (t_token *)vec_get(vec, i);
	second_token = (t_token *)vec_get(vec, i + 1);
	result = ft_strjoin_space(first_token->value, second_token->value);
	if (!result)
		return (NULL);
	combined = create_token(result, HEREDOC);
	if (!combined)
		return (NULL);
	return (combined);
}

/**
 * @brief Combines the given and next token into one token
 *
 * @param vec The vector to combine in of tokens
 * @param i The index of the first token
 * @return true If the tokens were combined
 * @return false If the tokens could not be combined
 */
bool	combine_heredoc(t_vector *vec, size_t i)
{
	t_token	*token;

	token = combine_tokens(vec, i);
	if (!token)
		return (false);
	if (!vec_replace(vec, i, token))
		return (false);
	return (true);
}

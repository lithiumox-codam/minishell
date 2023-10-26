/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 16:02:26 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/26 17:40:19 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	expand_sq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	char	*c;

	(*i)++;
	while (token->value[(*i)] != '\'')
	{
		c = malloc(sizeof(char));
		*c = token->value[(*i)];
		if (!vec_push(vec, c))
		{
			free(c);
			return (set_err(MALLOC, "expand_sq", data));
		}
		(*i)++;
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}

bool	expand_dq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	char	*c;

	(*i)++;
	while (token->value[(*i)] != '\"')
	{
		if (token->value[(*i)] == '$')
		{
			if (!expand_env(token, i, vec, data))
				return (false);
		}
		else
		{
			c = malloc(sizeof(char));
			*c = token->value[(*i)];
			if (!vec_push(vec, c))
			{
				free(c);
				return (set_err(MALLOC, "expand_dq", data));
			}
			(*i)++;
		}
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}

static t_env	*find_env(char *value, t_shell *data)
{
	t_env	*env_token;
	size_t	env_i;

	env_i = 0;
	while (env_i < (&data->env)->length)
	{
		env_token = vec_get(&data->env, env_i);
		if (ft_strcmp(value, env_token->key) == 0)
			break ;
		env_i++;
	}
	if (env_i == (&data->env)->length)
		return (NULL);
	return (env_token);
}

bool	expand_env(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	char	*value;
	size_t	start;
	t_env	*env_token;
	char	*c;

	start = (*i)++;
	while (token->value[(*i)] && token->value[(*i)] != ' '
		&& token->value[(*i)] != '\"' && token->value[(*i)] != '\''
		&& token->value[(*i)] != '$')
		(*i)++;
	value = ft_substr(token->value, start, (*i) - start);
	if (!value)
		return (set_err(MALLOC, "expand_env", data));
	env_token = find_env(value, data);
	free(value);
	if (!env_token)
		return (true);
	start = 0;
	while (env_token->value[start])
	{
		c = malloc(sizeof(char));
		*c = env_token->value[start];
		if (!vec_push(vec, c))
			return (set_err(MALLOC, "expand_env", data));
		start++;
	}
	return (true);
}

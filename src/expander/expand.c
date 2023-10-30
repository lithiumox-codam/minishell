/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 16:02:26 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/30 22:36:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	expand_sq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	(*i)++;
	while (token->value[(*i)] != '\'')
	{
		if (!char_vec_push(vec, token->value[(*i)]))
			return (set_err(MALLOC, "expand_sq", data));
		(*i)++;
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}

bool	expand_dq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	(*i)++;
	while (token->value[(*i)] != '\"')
	{
		if (token->value[(*i)] == '$')
		{
			if (!expand_env(token->value, i, vec, data))
				return (false);
		}
		else
		{
			if (!char_vec_push(vec, token->value[(*i)]))
				return (set_err(MALLOC, "expand_dq", data));
			(*i)++;
		}
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}

t_env	*compare_key(char *key, t_shell *data)
{
	t_env	*env_token;
	size_t	env_i;

	env_i = 0;
	while (env_i < (&data->env)->length)
	{
		env_token = vec_get(&data->env, env_i);
		if (ft_strcmp(key, env_token->key) == 0)
			break ;
		env_i++;
	}
	free (key);
	if (env_i == (&data->env)->length)
		return (NULL);
	return (env_token);
}

char	*get_env_key(char *str, size_t *i, t_shell *data)
{
	size_t	start;
	char	*key;

	start = (*i);
	while (str[(*i)] && (str[(*i)] >= 'A' && str[(*i)] <= 'Z'))
		(*i)++;
	key = ft_substr(str, start, (*i) - start);
	if (!key)
		set_err(MALLOC, "expand_env", data);
	return (key);
}
bool	expand_env(char *str, size_t *i, t_vector *vec, t_shell *data)
{
	char	*key;
	size_t	j;
	t_env	*env_token;

	(*i)++;
	if (str[(*i)] == '\0' || checkchar(str[(*i)], "\'\" "))
	{
		char_vec_push(vec, '$');
		return (true);
	}
	key = get_env_key(str, i, data);
	if (!key)
		return (false);
	env_token = compare_key(key, data);
	if (!env_token)
		return (true);
	j = 0;
	while (env_token->value[j])
	{
		if (!char_vec_push(vec, env_token->value[j]))
			return (set_err(MALLOC, "expand_env", data));
		j++;
	}
	return (true);
}

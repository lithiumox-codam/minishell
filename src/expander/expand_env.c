/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 16:02:26 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/03 18:50:19 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	push_status(size_t *i, t_vector *vec, t_shell *data)
{
	char	*exit_string;
	int		j;

	(*i)++;
	exit_string = ft_itoa(g_signal.exit_status);
	if (!exit_string)
		return (set_err(MALLOC, "push_status", data));
	j = 0;
	while (exit_string[j])
	{
		char_vec_push(vec, exit_string[j]);
		j++;
	}
	free(exit_string);
	return (true);
}

static t_env	*compare_key(char *key, char *str, size_t *i, t_shell *data)
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
	free(key);
	if (env_i == (&data->env)->length)
	{
		while (str[(*i)] && ft_isalnum(str[(*i)]))
			(*i)++;
		return (NULL);
	}
	return (env_token);
}

static char	*get_env_key(char *str, size_t *i, t_shell *data)
{
	size_t	start;
	char	*key;

	start = (*i);
	while (str[(*i)] && ft_isalnum(str[(*i)]))
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
	if (str[(*i)] == '?')
		return (push_status(i, vec, data));
	if (str[(*i)] == '\0' || checkchar(str[(*i)], "\'\" "))
		return (char_vec_push(vec, '$'));
	key = get_env_key(str, i, data);
	if (!key)
		return (false);
	env_token = compare_key(key, str, i, data);
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

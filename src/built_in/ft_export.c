/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 22:20:10 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/31 23:13:57 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

bool	compare_env_key(void *item, void *key)
{
	char	*str;

	str = ((t_env *)item)->key;
	if (ft_strcmp((char *)key, str) == 0)
		return (true);
	return (false);
}

static void	add_env(t_vector *env_vec, char *key, char *value)
{
	t_env	*token;
	char	*key_dup;
	char	*value_dup;

	key_dup = ft_strdup(key);
	value_dup = ft_strdup(value);
	if (!key_dup || !value_dup)
	{
		g_signal.exit_status = 1;
		return ;
	}
	token = (t_env *)malloc(sizeof(t_env));
	if (!token)
	{
		g_signal.exit_status = 1;
		return ;
	}
	token->key = key_dup;
	token->value = value_dup;
	if (!vec_push(env_vec, token))
	{
		g_signal.exit_status = 1;
		return ;
	}
}

void	ft_export(t_group *group, t_vector *env_vec)
{
	size_t	i;
	char	**env;
	t_env	*token;

	i = 1;
	while (group->args[i])
	{
		env = ft_split(group->args[i], '=');
		if (!env)
		{
			g_signal.exit_status = 1;
			return ;
		}
		token = (t_env *)vec_find_f(env_vec, compare_env_key, env[0]);
		if (token)
		{
			free(token->value);
			token->value = ft_strdup(env[1]);
		}
		else
			add_env(env_vec, env[0], env[1]);
		ft_free(env);
		i++;
	}
	g_signal.exit_status = 0;
}

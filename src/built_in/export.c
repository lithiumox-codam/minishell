/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 22:20:10 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/03 18:43:33 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	validate_input(t_group *group)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (group->args[i])
	{
		j = 0;
		while (group->args[i][j])
		{
			if (j == 0 && !ft_isalpha(group->args[i][j]))
			{
				printf("export: `%s': not a valid identifier 1\n",
					group->args[i]);
				g_signal.exit_status = 1;
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

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
	if (!value)
		value_dup = ft_strdup("");
	else
		value_dup = ft_strdup(value);
	printf("key: %s, value: %s\n", key_dup, value_dup);
	if (!key_dup || !value_dup)
	{
		if (key_dup)
			free(key_dup);
		if (value_dup)
			free(value_dup);
		return ;
	}
	token = (t_env *)malloc(sizeof(t_env));
	if (!token)
		return ;
	token->key = key_dup;
	token->value = value_dup;
	if (!vec_push(env_vec, token))
		return ;
}

void	ft_export(t_group *group, t_vector *env_vec)
{
	size_t	i;
	char	**env;
	t_env	*token;

	i = 1;
	while (group->args[i])
	{
		if (!validate_input(group))
			return ;
		env = ft_split(group->args[i], '=');
		if (!env)
			return ;
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

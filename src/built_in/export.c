/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 22:20:10 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/20 21:49:48 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	validate_input(char *arg, size_t *i, t_shell *data)
{
	size_t	j;

	j = 0;
	if (!ft_isalpha(arg[0]))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		data->error_type = CATCH_ALL;
		return ((*i)++, false);
	}
	while (arg[j] && arg[j] != '=')
		j++;
	return (true);
}

/**
 * @brief Helper function for vec_find_f
 *
 * @param item The item to compare
 * @param key The key to compare with
 * @return true If the key and item key are equal
 * @return false If the key and item key are not equal
 */
bool	compare_env_key(void *item, void *key)
{
	char	*str;

	str = ((t_env *)item)->key;
	if (ft_strcmp((char *)key, str) == 0)
		return (true);
	return (false);
}

/**
 * @brief Function to add a env to the env vector
 *
 * @param env_vec The vector to add the env token to
 * @param key The key of the env token
 * @param value The value of the env token (can be null so export
 * and env can function properly)
 */
static void	add_env(t_vector *env_vec, char *key, char *value)
{
	t_env	*token;
	char	*key_dup;
	char	*value_dup;

	key_dup = string_handler(key);
	value_dup = ft_strdup(value);
	if (!key_dup)
	{
		if (key_dup)
			free(key_dup);
		if (value_dup)
			free(value_dup);
		return ;
	}
	token = (t_env *)malloc(sizeof(t_env));
	if (!token)
	{
		free(key_dup);
		free(value_dup);
		return ;
	}
	token->key = key_dup;
	token->value = value_dup;
	if (!vec_push(env_vec, token))
		clear_token(token);
}

static void	export_helper(t_env *token, t_shell *data, char **env)
{
	if (token)
	{
		if (env[1])
		{
			free(token->value);
			token->value = ft_strdup(env[1]);
		}
	}
	else
		add_env(&data->env, env[0], env[1]);
}

/**
 * @brief The main export builtin function
 *
 * @param group The group struct that contains the arguments
 * @param env_vec The vector that contains the enviroment variables
 * @return void
 */
void	ft_export(t_group *group, t_shell *data)
{
	size_t	i;
	char	**env;
	t_env	*token;

	i = 1;
	print_env_dec(&data->env, group->args[1]);
	while (group->args[i])
	{
		if (!validate_input(group->args[i], &i, data))
			continue ;
		env = ft_export_split(group->args[i], '=');
		if (!env)
			return ;
		token = (t_env *)vec_find_f(&data->env, compare_env_key, env[0]);
		export_helper(token, data, env);
		ft_free(env);
		i++;
	}
	data->error_type = NO_ERROR;
}

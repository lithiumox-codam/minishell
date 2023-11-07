/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 02:54:34 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/07 16:02:23 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Initializes the enviroment variables
 *
 * @param env The enviroment variables
 */
void	init_env(char **env, t_vector *env_vec)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (!key)
			exit_mini("init_env", 1);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!value)
			exit_mini("init_env", 1);
		if (!vec_push(env_vec, create_env(key, value)))
			exit_mini("init_env", 1);
		i++;
	}
}

/**
 * @brief Create a env object
 *
 * @param key The key of the env
 * @param value The value of the env
 * @return t_env* The created env object
 */
t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	return (env);
}

/**
 * @brief Prints a env struct
 *
 * @param data The env struct
 * @param i The index of the env struct
 */
void	print_env(void *data, size_t i)
{
	t_env	*env;

	env = (t_env *)data;
	if (i == 0)
		printf("\033[1;36m├── Enviroment Vector 👇\n");
	else
		printf("\033[1;38m●\n");
	printf("\033[1;36m│\n");
	printf("├── Env %zu:\n", i);
	printf("│   ├── Key: %s\n", env->key);
	printf("│   ├── Value: %s\n", env->value);
	printf("│   └── Adress: %p\n", env);
	printf("\033[1;36m│\n");
	printf("\033[0m");
}

/**
 * @brief Clears a env struct
 *
 * @param data The env struct
 */
void	clear_env(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	free(env->key);
	free(env->value);
}

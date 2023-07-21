/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 02:54:34 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 03:54:58 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	clear_env(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	free(env->key);
	free(env->value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 18:52:54 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/21 18:26:53 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints the entire environment with 'declare -x' in front of it
 *
 * @param env The environment to print
 * @param arg_2 The second argument of the command if there is one
 * @return void
 */
void	print_env_dec(t_vector *env, char *arg_2)
{
	size_t	i;
	size_t	**arr;

	i = 0;
	if (arg_2)
		return ;
	arr = return_sorted_arr(env);
	while (i < env->length)
	{
		printf("declare -x %s=\"%s\"\n", ((t_env *)vec_get(env, *arr[i]))->key,
			((t_env *)vec_get(env, *arr[i]))->value);
		i++;
	}
	ft_free_size_t(arr, env->length);
}

/**
 * @brief Updates the value of an environment variable when it already exists or
 * creates a new one if it doesn't (used in cd to update PWD and OLDPWD)
 * @param env The environment vector
 * @param key The key to compare to
 * @param value The value to update or create
 * @return void
 */
void	update_or_create_env(t_vector *env, char *key, char *value)
{
	t_env	*env_var;

	env_var = vec_find_f(env, compare_env_key, key);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
	}
	else
	{
		if (!vec_push(env, create_env(ft_strdup(key), ft_strdup(value))))
			exit_mini("update_or_create_env", 1);
	}
}

/**
 * @brief A version of split that only splits on the first occurence of the
 * delimiter and treats the rest as one string
 *
 * @param src The string to split
 * @param delimiter The delimiter to split on
 * @return char** The splitted string
 */
char	**ft_export_split(char *src, char delimter)
{
	char	**ret;
	size_t	i;

	ret = malloc(sizeof(char *) * 3);
	if (!ret)
		exit_mini("ft_export_split", 1);
	i = 0;
	while (src[i] && src[i] != delimter)
		i++;
	ret[0] = ft_substr(src, 0, i);
	if (!ret[0])
		exit_mini("ft_export_split", 1);
	if (src[i] == delimter)
	{
		i++;
		ret[1] = ft_strdup(src + i);
		if (!ret[1])
			exit_mini("ft_export_split", 1);
	}
	else
		ret[1] = NULL;
	ret[2] = NULL;
	return (ret);
}

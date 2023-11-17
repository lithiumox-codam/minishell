/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 19:44:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/14 16:21:13 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "echo") == 0)
		return (true);
	return (false);
}

bool	is_special_builtin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "cd") == 0)
		return (true);
	return (false);
}

char	**combine_env(t_vector *env_vec)
{
	char **env;
	t_env *env_token;
	size_t i;

	i = 0;
	env = malloc(sizeof(char *) * (env_vec->length + 1));
	if (env == NULL)
		exec_err("combine_env", MALLOC);
	while (i < env_vec->length)
	{
		env_token = vec_get(env_vec, i);
		env[i] = ft_calloc(ft_strlen(env_token->key)
				+ ft_strlen(env_token->value) + 2, sizeof(char));
		ft_strcpy(env[i], env_token->key);
		ft_strcat(env[i], "=");
		ft_strcat(env[i], env_token->value);
		i++;
	}
	env[i] = NULL;
	return (env);
}

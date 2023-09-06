/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 18:11:09 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 13:00:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	signal;

/**
 * @brief	frees the main data struct
 * @param	data t_shell data
 * @param	close_shell true to free env and the struct
 * 						false to keep data and env
 *
 */
void	free_shell(t_shell *data, bool close_shell)
{
	vec_free(&data->token_vec);
	clear_exec(data->exec);
	if (close_shell)
	{
		vec_free(&data->env);
		free(data);
	}
}

/**
 * @brief Initializes the enviroment variables
 *
 * @param env The enviroment variables
 */
static void	init_env(char **env, t_vector *env_vec)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!key || !value)
			exit(1); // !TODO: error message
		if (!vec_push(env_vec, create_env(key, value)))
			exit(1);
		i++;
	}
}

/**
 * @brief Create a signal struct object
 *
 * @return t_signal The created signal struct
 */
void	create_signal_struct(void)
{
	signal.inte = false;
	signal.quit = false;
	signal.pipe = false;
}

/**
 * @brief Initializes the global variables
 *
 * @param bool if its the first init of minishell = true
 * @param env The enviroment variables
 * @return true When the initialization was succesfull
 * @return false When the initialization failed
 */
t_shell	*init_shell(char **env, bool first_init)
{
	t_shell	*data;

	if (first_init)
	{
		data = malloc(sizeof(t_shell));
		if (!data)
			exit_mini("failed to init data", 1);
		if (!vec_init(&data->token_vec, 3, sizeof(t_token), clear_token))
			exit_mini("failed to vec_init token_vec", 1);
		if (!vec_init(&data->env, 50, sizeof(t_env), clear_env))
			exit_mini("failed to vec_init env", 1);
		init_env(env, &data->env);
		data->exec = NULL;
		data->exit_status = 0;
		create_signal_struct();
	}
	else
	{
		if (!vec_init(&data->token_vec, 3, sizeof(t_token), clear_token))
			exit_mini("failed to vec_init env", 1);
		data->exec = NULL;
	}
}

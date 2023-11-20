/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 18:11:09 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/20 20:57:12 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief	frees the main data struct
 * @param	data t_shell data
 * @param	close_shell true to free env and the struct
 * 						false to keep data and env
 *
 */
void	free_shell(t_shell *data, bool close_shell)
{
	if (data->token_vec.data)
		vec_free(&data->token_vec);
	if (data->exec)
		clear_exec(&data->exec);
	data->exit_type = GOOD;
	if (close_shell)
	{
		vec_free(&data->env);
		free(data);
	}
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

	data = NULL;
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
		data->exit_type = GOOD;
		data->error_type = NO_ERROR;
		data->exit_msg = NULL;
	}
	else
	{
		if (!vec_init(&data->token_vec, 3, sizeof(t_token), clear_token))
			exit_mini("failed to vec_init env", 1);
		data->exec = NULL;
		data->exit_type = GOOD;
		data->exit_msg = NULL;
	}
	return (data);
}

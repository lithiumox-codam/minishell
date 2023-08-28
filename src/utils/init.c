/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:09:52 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/28 11:29:57 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

/**
 * @brief Initializes the enviroment variables
 *
 * @param env The enviroment variables
 */
static void	init_env(char **env)
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
		if (!g_data.env.push(&g_data.env, create_env(key, value)))
			exit(1);
		i++;
	}
}

/**
 * @brief Create a signal struct object
 *
 * @return t_signal The created signal struct
 */
static t_signal	create_signal_struct(void)
{
	t_signal	signal;

	signal.inte = false;
	signal.quit = false;
	signal.pipe = false;
	return (signal);
}

/**
 * @brief Initializes the global variables
 *
 * @param env The enviroment variables
 * @return true When the initialization was succesfull
 * @return false When the initialization failed
 */
bool	init(char **env)
{
	g_data.signal = create_signal_struct();
	if (!vec_init(&g_data.tokens, 3, sizeof(t_token), clear_token))
		return (false);
	if (!vec_init(&g_data.env, 50, sizeof(t_env), clear_env))
		return (false);
	g_data.exit_status = ft_strdup("0");
	if (!g_data.exit_status)
		return (false);
	init_env(env);
	return (true);
}

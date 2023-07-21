/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:09:52 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 03:32:39 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

static void	init_env(char **envp)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (!key || !value)
			exit(1);
		if (!g_data.env.push(&g_data.env, create_env(key, value)))
			exit(1);
		i++;
	}
}

static t_signal	create_signal_struct(void)
{
	t_signal	signal;

	signal.inte = false;
	signal.quit = false;
	signal.pipe = false;
	return (signal);
}

bool	init(char **env)
{
	g_data.signal = create_signal_struct();
	ft_vec_init(&g_data.tokens, 3, sizeof(t_token), clear_token);
	ft_vec_init(&g_data.env, 50, sizeof(t_env), clear_env);
	g_data.exit_status = ft_strdup("0");
	if (!g_data.exit_status)
		return (false);
	init_env(env);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 20:09:52 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 20:35:00 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

static t_signal	create_signal_struct(void)
{
	t_signal	signal;

	signal.inte = false;
	signal.quit = false;
	signal.pipe = false;
	return (signal);
}

bool	init(void)
{
	g_data.signal = create_signal_struct();
	ft_vec_init(&g_data.tokens, 3, sizeof(t_token));
	ft_vec_init(&g_data.env, 50, sizeof(t_env));
	g_data.exit_status = ft_strdup("0");
	if (!g_data.exit_status)
		return (false);
	return (true);
}

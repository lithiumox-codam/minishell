/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder_special.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 15:01:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/31 17:35:27 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

int long long	ft_exit_atoi(char *str)
{
	size_t			i;
	int long long	output;

	output = 0;
	i = 0;
	while (checkchar(str[i], "1234567890"))
	{
		output = (output * 10) + (str[i] - '0');
		i++;
	}
	return (output);
}

void	ft_exit(t_group *group, t_shell *data)
{
	size_t			i;
	int long long	output;

	i = 0;
	while (group->args[i])
		i++;
	if (i == 1)
	{
		free_shell(data, true);
		exit(0);
	}
	if (i > 2)
	{
		write(1, "minishell: exit: too many arguments\n", 37);
		g_signal.exit_status = 1;
		return ;
	}
	i = 0;
	while (group->args[1][i])
	{
		if (!ft_isdigit(group->args[1][i]))
		{
			write(1, "minishell: exit: ", 17);
			write(1, group->args[1], ft_strlen(group->args[1]));
			write(1, ": numeric argument required\n", 28);
			g_signal.exit_status = 2;
			return ;
		}
		i++;
	}
	output = ft_exit_atoi(group->args[1]);
	free_shell(data, true);
	exit(output);
}

void	ft_cd(t_group *group)
{
	(void)group;
	printf("built_in cd placeholder\n");
	g_signal.exit_status = 0;
}

static bool	compare_env_key(void *item, void *key)
{
	t_env	*token;
	char	*str;

	token = (t_env *)item;
	str = (char *)key;
	if (ft_strcmp(token->key, str) == 0)
		return (true);
	return (false);
}

void	ft_unset(t_group *group, t_vector *env_vec)
{
	// size_t	i;
	// i = 0;
	// while
	// print_env(vec_find_f(env_vec, group->args[1], compare_env_key));
	(void)env_vec;
	(void)group;
	g_signal.exit_status = 0;
}

static void	set_env(t_vector *env_vec, char *key, char *value)
{
	t_env	*token;

	token = create_env(key, value);
	print_env(token, 0);
	print_vector(env_vec, print_env);
	if (!token && !vec_push(env_vec, token))
		g_signal.exit_status = 1;
	g_signal.exit_status = 0;
}

void	ft_export(t_group *group, t_vector *env_vec)
{
	size_t	i;
	char	**env;
	t_env	*token;

	i = 1;
	while (group->args[i])
	{
		token = vec_find_f(env_vec, compare_env_key, group->args[i]);
		if (token)
			token->value = group->args[i];
		env = ft_split(group->args[i], '=');
		if (!env)
			g_signal.exit_status = 1;
		if (env[1])
			set_env(env_vec, env[0], env[1]);
		else
			set_env(env_vec, env[0], "");
		i++;
	}
	g_signal.exit_status = 0;
}

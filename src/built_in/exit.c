/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 15:01:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 22:03:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static bool	check_args(t_group *group, t_shell *data)
{
	if (group->args[1] == NULL)
	{
		free_shell(data, true);
		exit(0);
	}
	if (group->args[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		data->error_type = CATCH_ALL;
		return (false);
	}
	return (true);
}

static void	numeric_error(t_shell *data, char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	data->error_type = MISUSE_OF_SHELL;
}

static char	*return_start(t_shell *data, char *str)
{
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	if (str[i] == '-')
		return (free_shell(data, true), exit(156), NULL);
	if (str[i] == '+')
	{
		offset++;
		i++;
	}
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (numeric_error(data, str), NULL);
	return (&str[offset]);
}

/**
 * @brief The exit command will exit the shell with the given exit code.
 *
 * @param group The group struct with the args
 * @param data The shell struct
 * @return void
 */
void	ft_exit(t_group *group, t_shell *data)
{
	int long long	output;
	char			*str;

	if (!check_args(group, data))
		return ;
	str = return_start(data, group->args[1]);
	if (!str)
		return ;
	output = ft_exit_atoi(str);
	free_shell(data, true);
	exit(output);
}

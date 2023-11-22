/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 15:01:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 22:48:24 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Simple atoi function that returns a int long long
 *
 * @param str The string to convert
 * @return int long long The converted string in a int long long
 */
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

/**
 * @brief Checks if the arguments are valid for the exit command
 * think about exit 1 2 3 (too many arguments) or exit hello (not a number)
 *
 * @param group
 * @param data
 * @return true
 * @return false
 */
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

/**
 * @brief Simple error message for when the argument is not a number
 *
 * @param data The shell struct to set the error type
 * @param str The string that is not a number
 */
static void	numeric_error(t_shell *data, char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	data->error_type = MISUSE_OF_SHELL;
}

/**
 * @brief Returns the start of the string if it is a valid number
 * if not, it will print an error message and return NULL
 *
 * @param data The shell struct
 * @param str The string to check
 * @return char* The start of the string if it is a valid number
 */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:54:14 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/15 16:58:29 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Returns the value in the environment for the given key
 *
 * @param key The key to search for
 * @return char* The value in the environment or NULL if not found
 */
char	*find_in_env(char *key, t_shell *data)
{
	size_t	i;

	i = 0;
	while (i < &data->env.length)
	{
		if (ft_strcmp(((t_env *)vec_get(&data->env, i))->key, key + 1) == 0)
			return (((t_env *)vec_get(&data->env, i))->value);
		i++;
	}
	return (NULL);
}
/**
 * @brief a function that pulls a string apart based on spaces and dollar signs
 *
 * @param str the string to split
 * @return char** the split string or NULL if malloc fails
 */
// The idea is that "Dit is een $TEST$TEST" becomes ["Dit", "is", "een",
	"$TEST", "$TEST"]
char	**split_env(char *str)
{
	size_t	i;
	size_t	j;
	char	**ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret[j] = ft_substr(str, 0, i);
			if (!ret[j])
				return (NULL);
			str = str + i;
			i = 0;
			j++;
		}
		i++;
	}
	ret[j] = ft_strdup(str);
	if (!ret[j])
		return (NULL);
	ret[j + 1] = NULL;
	return (ret);
}

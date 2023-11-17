/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/14 22:07:22 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/14 22:21:52 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Gets the amount of splits that will be made
 * so the double pointer can be 
 * 
 * This assumes it should split on spaces and dollar signs
 * and add one for the last split
 *
 * @param str The string to split
 * @return size_t The amount of splits
 */
static size_t get_split_amount(char *str)
{
    size_t i;
    size_t splits;

    i = 0;
    splits = 0;

    while (str[i])
    {
        if (str[i] == '$' || str[i] == ' ')
            splits++;
        // check if the next character is a dollar sign or space and if not skip over it
        i++;
    }
    
}

/**
 * @brief Splits the string on spaces and dollar signs including the string
 * between the dollar signs
 *
 * @param data The data struct
 * @return char ** The split string
 */
char	**split_env(char *str, t_shell *data)
{
    
}

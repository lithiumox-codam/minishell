/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/31 20:14:30 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

group the tokens into their executable groups

< infile cat | cat -e | wc > outfile

Groups:
< infile == start_I_redirect
wc > outfile == end_O_redirect

cat == left_process (pipe on the right side, no pipe on the left side)
cat -e == middle_process (pipe on the left side and pipe on the right side)
wc == right_process (pipe on the right side, no pipe on the left side)


< infile cat | cat -e > outfile | echo "hello" | wc

redirects are only handled by main process if they are on the outside, if redirects are not fully on the outside they are handled by the child_processes

groups:
< infile == start_I_redirect

cat == left_process
cat -e > outfile == middle_process
echo "hello" = middle_process
wc = right_process

*/

#include <minishell.h>


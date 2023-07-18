/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/18 22:47:30 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pretty_print_vector(t_vector *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->lenght)
	{
		token = (t_token *)ft_vec_get(tokens, i);
		if (token != NULL)
		{
			printf("\033[1;32m●\n");
			printf("\033[1;34m│\n");
			printf("├── Token %zu:\n", i++);
			printf("│   ├── Value: %s\n", token->value);
			printf("│   ├── Type: %i\n", token->type);
			printf("│   └── Adress: %p\n", token);
			printf("\033[1;34m│\n");
			printf("\033[0m");
		}
	}
}

static void	clear_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->value);
}

static void	uncapitalize_token(void *data)
{
	t_token	*token;
	char	*temp;

	token = (t_token *)data;
	temp = token->value;
	while (*temp)
	{
		*temp = ft_tolower(*temp);
		temp++;
	}
}

static void	tokenize(char *input, t_vector t)
{
	char	**tmp;
	t_token	token;
	size_t	i;

	i = 0;
	tmp = ft_split(input, ' ');
	while (tmp[i])
	{
		token.type = DOUBLE_QUOTE;
		if (i % 3)
			token.type = SINGLE_QUOTE;
		token.value = tmp[i];
		ft_vec_push(&t, (void *)&token);
		i++;
	}
	free(tmp);
	ft_vec_apply(&t, uncapitalize_token);
	pretty_print_vector(&t);
	ft_vec_free(&t, clear_token);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_vector	t;

	(void)env;
	ft_vec_init(&t, 5, sizeof(t_token));
	if (ac == 2)
	{
		tokenize(av[1], t);
		return (0);
	}
	while (1)
	{
		input = readline("\n\033[1;32mminishell$ \033[0m");
		if (!input)
			break ;
		add_history(input);
		if (!ft_strcmp(input, "exit"))
			return (free(input), 0);
		else
			tokenize(input, t);
		free(input);
		ft_vec_init(&t, 5, sizeof(t_token));
	}
	return (0);
}

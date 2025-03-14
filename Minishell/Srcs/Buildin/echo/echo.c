/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:00:57 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	print_args(char **args, int start, int newline)
{
	int	i;
	int	first;

	first = 1;
	i = start;
	while (args[i] != NULL)
	{
		if (!first)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		first = 0;
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	echo(char *input, int *g_exit_status)
{
	char	**args;
	int		i;
	int		newline;

	args = ft_split(input, ' ');
	if (args == NULL)
	{
		*g_exit_status = 1;
		return ;
	}
	i = 1;
	newline = 1;
	while (args[i] != NULL && is_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	print_args(args, i, newline);
	free_env_array(args);
	*g_exit_status = 0;
}

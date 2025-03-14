/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:10:15 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:10:15 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	display_error(char *msg, int result, int *status)
{
	printf("%s\n", msg);
	*status = result;
	return (1);
}

static int	check_exit_args(char **cmds, int *status)
{
	int	i;

	i = 1;
	if (count_double_ptr(cmds) > 2)
	{
		if (strs_arenum(cmds) == 0)
			return (display_error("Numerical Arguments Required!", 2, status));
		return (display_error("too many arguments", 1, status));
	}
	while (cmds[i])
	{
		if (str_isnum(cmds[i]) == 0)
			return (display_error("Numerical Arguments Required!", 2, status));
		*status = ft_atoi(cmds[i]);
		i++;
	}
	return (1);
}

int	ft_exit(char *msg, int *status)
{
	char	**cmds;
	int		result;

	cmds = ft_split(msg, ' ');
	if (!cmds)
		return (0);
	if (ft_strncmp(msg, "exit", 4) != 0)
	{
		free_env_array(cmds);
		return (0);
	}
	result = check_exit_args(cmds, status);
	free_env_array(cmds);
	return (result);
}

char	*ft_strskip_spaces(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	return (str + i);
}

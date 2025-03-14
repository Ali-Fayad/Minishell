/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuct_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:18:59 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:28 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_variables(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**transfer_to_2d_array(t_env *head)
{
	int		count;
	char	**array_2d;
	t_env	*current;
	int		i;

	count = count_variables(head);
	array_2d = (char **)malloc((count + 1) * sizeof(char *));
	current = head;
	i = 0;
	while (current != NULL)
	{
		array_2d[i] = strdup(current->var);
		if (array_2d[i] == NULL)
		{
			while (i > 0)
			{
				free(array_2d[--i]);
			}
			return (free(array_2d), NULL);
		}
		i++;
		current = current->next;
	}
	array_2d[i] = NULL;
	return (array_2d);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (env_array == NULL)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

char	*strip_dot_slash(char *cmd)
{
	if (cmd != NULL && cmd[0] == '.' && cmd[1] == '/')
		return (cmd + 2);
	return (NULL);
}

int	is_only_spaces(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:44:49 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:32 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exit_status_result(char *msg, int *g_exit_status)
{
	char	*exit_status_str;
	char	*result;

	exit_status_str = ft_itoa(*g_exit_status);
	if (!exit_status_str)
		return (NULL);
	if (msg[1] == '\0')
		return (exit_status_str);
	result = malloc(strlen(exit_status_str) + strlen(msg + 1) + 1);
	if (!result)
	{
		free(exit_status_str);
		return (NULL);
	}
	ft_strcpy(result, exit_status_str);
	ft_strcat(result, msg + 1);
	free(exit_status_str);
	return (result);
}

char	*find_env_var(char *msg, t_env **head, int *g_exit_status)
{
	char	*result;
	char	*key;

	if (!msg || !head)
		return (NULL);
	if (msg[0] == '?')
		return (get_exit_status_result(msg, g_exit_status));
	if (msg[0] == '$')
		key = msg + 1;
	else
		key = msg;
	result = get_env_value(key, head);
	return (result);
}

void	free_cmds(char **cmds, int i)
{
	int	j;

	if (!cmds)
		return ;
	j = 0;
	while (j < i)
	{
		free(cmds[j]);
		j++;
	}
	free(cmds);
}

char	*get_env_value(char *new, t_env **head)
{
	t_env	*current;
	char	*search_key;
	size_t	len;

	len = ft_strlen(new);
	search_key = (char *)malloc(len + 2);
	if (!search_key)
		return (NULL);
	v_strcpy(search_key, new);
	v_strcat(search_key, "=");
	current = *head;
	while (current)
	{
		if (current->check == 0
			&& ft_strncmp(current->var, search_key, len + 1) == 0)
		{
			free(search_key);
			return (current->var + len + 1);
		}
		current = current->next;
	}
	free(search_key);
	return (NULL);
}

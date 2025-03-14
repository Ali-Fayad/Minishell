/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:08:15 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:08:15 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	max_env(t_env **head)
{
	t_env	*current;
	int		max_len;
	int		len;

	current = *head;
	max_len = 0;
	while (current)
	{
		if (current->check == 0)
		{
			len = 0;
			while (current->var[len])
				len++;
			if (len > max_len)
				max_len = len;
		}
		current = current->next;
	}
	return (max_len);
}

int	dollar_counter(char *str, t_env **head)
{
	int		i;
	int		count;
	int		max_len;

	i = 0;
	count = 0;
	max_len = max_env(head);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			count++;
			while (ft_isalnum(str[i]))
				i++;
			count += max_len;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

int	c_dollar(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		if (msg[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

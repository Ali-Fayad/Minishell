/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:08:49 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:08:49 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_helper(char *msg)
{
	int		i;
	int		count;
	char	type;

	i = 0;
	count = ft_strlen(msg);
	while (msg[i])
	{
		if (msg[i] == '$')
		{
			if (msg[i + 1] == '"' || msg[i + 1] == '\'')
			{
				type = msg[++i];
				i++;
				while (msg[i] && msg[i] != type)
					i++;
				if (msg[i] == type)
					i++;
			}
		}
		else
			i++;
	}
	return (count);
}

char	*dollar_helper(char *msg)
{
	char	*result;
	int		i;
	int		j;
	char	type;

	result = malloc(count_helper(msg) + 1);
	i = 0;
	j = 0;
	while (msg[i])
	{
		if (msg[i] == '$' && (msg[i + 1] == '"' || msg[i + 1] == '\''))
		{
			type = msg[++i];
			i++;
			while (msg[i] && msg[i] != type)
				result[j++] = msg[i++];
			if (msg[i] == type)
				i++;
		}
		else
			result[j++] = msg[i++];
	}
	result[j] = '\0';
	return (result);
}

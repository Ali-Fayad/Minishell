/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:58:05 by afayad            #+#    #+#             */
/*   Updated: 2025/03/12 21:32:28 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquotes(char *msg)
{
	int		i;
	char	type;
	int		quotes;

	i = 0;
	quotes = 1;
	type = 0;
	while (msg[i])
	{
		if (msg[i] == 34 || msg[i] == 39)
		{
			if (type == 0 || type == msg[i])
			{
				quotes = -quotes;
				type = msg[i];
			}
		}
		i++;
	}
	if (quotes == -1)
		return (0);
	return (1);
}

int	count_quotes(char *msg)
{
	int		count;
	int		i;
	char	type;

	i = 0;
	count = 0;
	while (msg[i])
	{
		if (msg[i] == 39 || msg[i] == 34)
		{
			type = msg[i];
			i++;
			while (msg[i] && msg[i] != type)
				i++;
			if (!msg[i])
				return (-1);
			count++;
		}
		if (msg[i])
			i++;
	}
	return (count);
}

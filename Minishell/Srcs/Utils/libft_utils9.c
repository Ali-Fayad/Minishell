/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:13:58 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:13:58 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

char	*ft_str_insert(char *str, char *insert, size_t index)
{
	size_t	len_str;
	size_t	len_insert;
	char	*new_str;
	size_t	i;
	size_t	j;

	len_str = ft_strlen(str);
	len_insert = ft_strlen(insert);
	new_str = malloc(len_str + len_insert + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < index)
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (j < len_insert)
		new_str[i++] = str[j++];
	while (i < len_str + len_insert)
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	return (new_str);
}

int	str_isnum(char *msg)
{
	int	i;

	i = 0;
	if (msg[i] == '+' || msg[i] == '-')
		i++;
	while (msg[i])
	{
		if (msg[i] < '0' || msg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	strs_arenum(char **msg)
{
	int	i;

	i = 1;
	while (msg[i] != NULL)
	{
		if (!str_isnum(msg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_double_ptr(char **msg)
{
	int	count;

	count = 0;
	while (msg[count] != NULL)
		count++;
	return (count);
}

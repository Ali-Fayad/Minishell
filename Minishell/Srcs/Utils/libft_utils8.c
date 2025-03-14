/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:07:38 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes(char *str)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(ft_strlen(str) + 3);
	if (!result)
		return (NULL);
	result[i++] = '"';
	while (*str)
	{
		result[i++] = *str++;
	}
	result[i++] = '"';
	result[i] = '\0';
	return (result);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*char_to_string(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	ft_isalpha(int c)
{
	if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
	{
		return (0);
	}
	return (1);
}

void	ft_putnbr(int nb)
{
	char	*num;

	num = "0123456789";
	if (nb == -2147483648)
	{
		write (1, "-2", 2);
		nb = 147483648;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		write(1, &(num[nb]), 1);
}

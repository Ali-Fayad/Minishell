/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:39:11 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:19 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	number;
	unsigned int	length;

	length = ft_number_size(n);
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		number = -n;
	}
	else
		number = n;
	if (number == 0)
		string[0] = '0';
	string[length] = '\0';
	while (number != 0)
	{
		string[length - 1] = (number % 10) + '0';
		number = number / 10;
		length--;
	}
	return (string);
}

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	if (dst_len >= size)
		dst_len = size;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < size - dst_len)
	{
		ft_memcpy(dest + dst_len, src, src_len + 1);
	}
	else
	{
		ft_memcpy(dest + dst_len, src, size - dst_len - 1);
		dest[size - 1] = '\0';
	}
	return (dst_len + src_len);
}

char	*remove_last_char(char *msg)
{
	size_t	len;
	char	*new_msg;

	len = ft_strlen(msg);
	if (len == 0)
		return (msg);
	new_msg = malloc(len);
	if (!new_msg)
		return (NULL);
	ft_memcpy(new_msg, msg, len - 1);
	new_msg[len - 1] = '\0';
	free(msg);
	return (new_msg);
}

char	*last_char_ptr(char *msg)
{
	return (&msg[strlen(msg) - 1]);
}

void	print_double_ptr(char **args)
{
	int	i;

	if (args[0] == NULL)
	{
		printf("its null!\n");
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
}

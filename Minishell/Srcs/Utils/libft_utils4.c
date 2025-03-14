/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:37:56 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:12 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (s < d && d < s + n)
	{
		s += n;
		d += n;
		while (n--)
		{
			*--d = *--s;
		}
	}
	else
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}

char	*remove_quotes_and_equals(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '=')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

int	ft_search(t_env *head, char *msg)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (strncmp(current->var, msg, strlen(msg)) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

void	remove_quotes(char *str)
{
	char	*read_ptr;
	char	*write_ptr;
	int		in_quotes;

	read_ptr = str;
	write_ptr = str;
	in_quotes = 0;
	while (*read_ptr)
	{
		if (*read_ptr == '"')
		{
			in_quotes = !in_quotes;
			read_ptr++;
			continue ;
		}
		if (in_quotes || *read_ptr != '"')
		{
			*write_ptr = *read_ptr;
			write_ptr++;
		}
		read_ptr++;
	}
	*write_ptr = '\0';
}

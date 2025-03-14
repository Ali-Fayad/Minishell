/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:20:08 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:10 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	d = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == d)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	actual_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	actual_len = s_len - start;
	if (len > actual_len)
		len = actual_len;
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	const char	*copy;
	char		*result;
	size_t		i;

	i = 0;
	copy = src;
	result = dest;
	while (i < n)
	{
		result[i] = copy[i];
		i++;
	}
	return (result);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	if (size > 0)
	{
		if (src_len < size - 1)
		{
			copy_len = src_len;
		}
		else
			copy_len = size - 1;
		ft_memcpy(dest, src, copy_len);
		dest[copy_len] = '\0';
	}
	return (src_len);
}

int	ft_catchchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

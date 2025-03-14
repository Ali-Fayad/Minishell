/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:09:23 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:08 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (i < n - 1) && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, str, len + 1);
	return (dup);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*res;
	char			d;

	d = (char) c;
	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			res = (char *) &s[i];
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (res);
}

char	*ft_strskip(char *str, size_t size)
{
	char	*result;
	size_t	len;

	if (!str || ft_strlen(str) == 0)
		return (NULL);
	str += size;
	while (*str && *str == ' ')
		str++;
	if (!*str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	len = ft_strlen(result);
	while (len > 0 && result[len - 1] == ' ')
	{
		result[len - 1] = '\0';
		len--;
	}
	if (len == 0)
		return (free(result), NULL);
	return (result);
}

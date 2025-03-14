/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:16:33 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:03 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

void	ft_strncpy(char *str, char const *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		str[i] = (char)src[i];
		i++;
	}
	str[i] = '\0';
}

static void	ft_helper(char c, char const *s, char **strs, int *k)
{
	int	j;
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			strs[*k] = malloc((j + 1) * sizeof(char));
			ft_strncpy(strs[(*k)++], (char *)s + i, j);
			i += j;
		}
		else
			i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		k;

	if (!s)
		return (NULL);
	strs = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	k = 0;
	if (strs == NULL)
		return (NULL);
	ft_helper(c, s, strs, &k);
	strs[k] = NULL;
	return (strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:44:17 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:09 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_strings_in_loop(char **strs, char **copy,
	int count, int checker)
{
	int		i;
	char	*copy_dup;

	i = 0;
	while (i < count)
	{
		if (strs[i] && count_here_docs(strs[i]) > 0)
		{
			copy_dup = ft_strdup(strs[i]);
			copy[i] = split_heredoc_helper(copy_dup, checker);
			free(copy_dup);
			if (!copy[i])
				return (0);
		}
		else
		{
			copy[i] = ft_strdup(strs[i]);
			if (!copy[i])
				return (0);
		}
		i++;
	}
	copy[i] = NULL;
	return (1);
}

char	**process_heredocs_with_copy(char **strs, int checker)
{
	int		count;
	char	**copy;

	count = 0;
	while (strs[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	if (!process_strings_in_loop(strs, copy, count, checker))
		return (NULL);
	return (copy);
}

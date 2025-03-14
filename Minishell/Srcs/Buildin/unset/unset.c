/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:48:26 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:44 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split_array)
{
	int	i;

	if (!split_array)
		return ;
	i = 0;
	while (split_array[i] != NULL)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

void	remove_env(t_env **head, char *msg)
{
	t_env	*current;
	t_env	*prev;
	size_t	msg_len;

	if (!msg || ft_catchchar(msg, '=') != -1)
		return ;
	current = *head;
	prev = NULL;
	msg_len = ft_strlen(msg);
	while (current)
	{
		if (ft_strncmp(current->var, msg, msg_len) == 0
			&& (current->var[msg_len] == '=' || current->var[msg_len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->var);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	unset(t_env **head, char *msg)
{
	char	*result;
	char	**args;
	int		i;

	if (!msg)
		return ;
	result = ft_strskip(msg, 5);
	if (!result)
		return ;
	args = ft_split(result, ' ');
	if (!args)
	{
		free(result);
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		change_check(args[i], head, 1);
		i++;
	}
	free(result);
	ft_free_split(args);
}

int	is_first_word_directory(char *msg)
{
	char		*word;
	struct stat	buf;
	int			i;

	if (!msg)
		return (0);
	i = 0;
	while (msg[i] && msg[i] != ' ' && msg[i] != '\t')
		i++;
	word = strndup(msg, i);
	if (!word)
		return (0);
	if (stat(word, &buf) == -1)
	{
		free(word);
		return (0);
	}
	free(word);
	return (S_ISDIR(buf.st_mode));
}

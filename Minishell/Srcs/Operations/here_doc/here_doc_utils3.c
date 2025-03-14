/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:05:48 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:11 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_counter(char *msg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (msg[i])
	{
		if (msg[i] == '<' && msg[i + 1] == '<')
		{
			i += 2;
			while (msg[i] && msg[i] != '<' && msg[i] != '>')
				i++;
			count += 10;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

static int	extract_heredoc_delimiter(char **input, char **here_docs,
		int *doc_count)
{
	char	*start;
	char	*end;

	*input += 2;
	while (**input == ' ' || **input == '\t')
		(*input)++;
	start = *input;
	while (**input && ft_strncmp(*input, "<", 1) != 0
		&& ft_strncmp(*input, ">", 1) != 0)
		(*input)++;
	end = *input;
	here_docs[*doc_count] = ft_strndup(start, end - start);
	if (!here_docs[*doc_count])
		return (0);
	(*doc_count)++;
	return (1);
}

void	extract_heredoc(char *input)
{
	char	**here_docs;
	int		doc_count;

	here_docs = (char **)malloc(sizeof(char *) * heredoc_counter(input));
	if (!here_docs)
		return ;
	doc_count = 0;
	while (*input)
	{
		if (ft_strncmp(input, "<<", 2) == 0)
		{
			if (!extract_heredoc_delimiter(&input, here_docs, &doc_count))
				break ;
		}
		else
			input++;
	}
	here_docs[doc_count] = NULL;
	if (doc_count > 0)
		here_doc(here_docs);
	free_env_array(here_docs);
}

int	c_heredoc(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		if (msg[i] == '<')
		{
			i++;
			if (msg[i] == '<')
			{
				i++;
				if (msg[i] == '<')
					continue ;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

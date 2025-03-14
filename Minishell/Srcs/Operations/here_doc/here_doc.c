/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:49:25 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:13 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_input(char **end_marker, int *i)
{
	char	*input_line;
	char	*input_line_s;
	char	*input_line_q;

	input_line = readline("> ");
	if (input_line == NULL)
		return (0);
	input_line_s = remove_spaces(end_marker[*i]);
	input_line_q = ft_quotes(input_line_s);
	if (ft_strcmp(input_line, input_line_q) == 0)
	{
		if (end_marker[*i + 1] == NULL)
			return (free(input_line), free(input_line_q),
				free(input_line_s), 1);
		else
		{
			(*i)++;
			clear_file("tmp.txt");
		}
	}
	else if (ft_strlen(input_line) > 0)
		append_chars_to_file("tmp.txt", input_line);
	return (free(input_line), free(input_line_q),
		free(input_line_s), 2);
}

void	here_doc(char **end_marker)
{
	int	i;
	int	result;

	if (end_marker == NULL)
		return ;
	i = 0;
	clear_file("tmp.txt");
	while (1)
	{
		result = process_heredoc_input(end_marker, &i);
		if (result == 0)
			break ;
		if (result == 1)
			return ;
	}
}

static int	process_heredoc_input2(char *end_marker)
{
	char	*input_line;
	char	*input_line_s;
	char	*input_line_q;

	input_line = readline("> ");
	if (!input_line)
		return (0);
	input_line_s = remove_spaces(end_marker);
	if (!input_line_s)
		return (free(input_line), 0);
	input_line_q = ft_quotes(input_line_s);
	free(input_line_s);
	if (!input_line_q)
		return (free(input_line), 0);
	if (ft_strcmp(input_line, input_line_q) == 0)
		return (free(input_line), free(input_line_q), 1);
	if (ft_strlen(input_line) > 0)
		append_chars_to_file("tmp.txt", input_line);
	return (free(input_line), free(input_line_q), 2);
}

void	here_doc2(char *end_marker)
{
	int	result;

	if (!end_marker)
		return ;
	clear_file("tmp.txt");
	while (1)
	{
		result = process_heredoc_input2(end_marker);
		if (result == 0)
			break ;
		if (result == 1)
			return ;
	}
}

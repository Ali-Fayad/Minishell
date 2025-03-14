/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:19:09 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:01 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(t_splitting_pipe *norm, char current_char)
{
	if (current_char == '\'')
	{
		if (norm->quotes != 2)
		{
			if (norm->quotes == 1)
				norm->quotes = 0;
			else
				norm->quotes = 1;
		}
	}
	else if (current_char == '\"')
	{
		if (norm->quotes != 1)
		{
			if (norm->quotes == 2)
				norm->quotes = 0;
			else
				norm->quotes = 2;
		}
	}
}

static	int	handle_pipe(t_splitting_pipe *norm)
{
	norm->args[norm->k] = ft_strndup(norm->tmp, norm->j);
	if (!norm->args[norm->k])
		return (0);
	norm->k++;
	norm->j = 0;
	free(norm->tmp);
	norm->tmp = NULL;
	return (1);
}

static int	append_to_tmp(t_splitting_pipe *norm, char *msg)
{
	if (!norm->tmp)
	{
		norm->tmp = malloc(strlen(msg) + 1);
		if (!norm->tmp)
			return (0);
	}
	norm->tmp[norm->j] = norm->current_char;
	norm->j++;
	norm->tmp[norm->j] = '\0';
	return (1);
}

int	init_splitting_pipe(t_splitting_pipe *norm, char *msg)
{
	norm->i = 0;
	norm->j = 0;
	norm->k = 0;
	norm->quotes = 0;
	norm->args = malloc(sizeof(char *) * (strlen(msg) / 2 + 1));
	if (!norm->args)
		return (0);
	norm->tmp = NULL;
	return (1);
}

int	process_input_string2(t_splitting_pipe *norm, char *msg)
{
	while (msg[norm->i])
	{
		norm->current_char = msg[norm->i];
		handle_quotes(norm, norm->current_char);
		if (norm->current_char == '|' && norm->quotes == 0)
		{
			if (!handle_pipe(norm))
				return (0);
		}
		else
		{
			if (!append_to_tmp(norm, msg))
				return (0);
		}
		norm->i++;
	}
	return (1);
}

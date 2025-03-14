/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:27:11 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_redirection(char *msg, int *i, int *g_exit_status)
{
	int		count;
	int		start;
	char	*tmp;
	char	*tmp_s;

	count = 1;
	if (msg[*i + 1] == msg[*i])
	{
		count++;
		(*i)++;
	}
	start = *i + 1;
	(*i)++;
	while (msg[*i] && msg[*i] != '>' && msg[*i] != '<')
		(*i)++;
	tmp = ft_substr(msg, start, *i - start);
	if (tmp == NULL)
		return ;
	tmp_s = remove_spaces(tmp);
	if (msg[start - count] == '<')
		input_op2(tmp_s, g_exit_status, count);
	else
		output_op2(tmp_s, g_exit_status, count);
	free(tmp);
	free(tmp_s);
}

void	op_redirection(char *msg, int *g_exit_status)
{
	int	i;

	i = 0;
	extract_heredoc(msg);
	while (msg[i])
	{
		if (msg[i] == '<' || msg[i] == '>')
			process_redirection(msg, &i, g_exit_status);
		else
			i++;
	}
}

int	catch_op(char *msg)
{
	int		i;
	int		quotes;
	char	type;

	i = 0;
	quotes = 1;
	type = 0;
	while (msg[i])
	{
		if (msg[i] == 34 || msg[i] == 39)
		{
			if (msg[i] == type || type == 0)
			{
				type = msg[i];
				quotes = -quotes;
			}
		}
		if ((msg[i] == 60 || msg[i] == 62) && quotes == 1)
			return (i);
		i++;
	}
	return (-1);
}

static t_op	init_op_struct(char *msg, int i)
{
	t_op	op;

	if (i != 0)
	{
		op.first = ft_substr(msg, 0, i);
		op.second = ft_substr(msg, i, ft_strlen(msg) - i);
		op.i = i;
		if (op.first && is_only_spaces(op.first))
		{
			free(op.first);
			op.first = NULL;
		}
	}
	else
	{
		op.first = NULL;
		op.second = ft_substr(msg, i, ft_strlen(msg) - i);
		op.i = i;
	}
	return (op);
}

t_op	op_extract_command(char *msg)
{
	int		i;
	char	type;
	int		quotes;
	t_op	op;

	i = 0;
	quotes = 1;
	type = 0;
	while (msg[i])
	{
		if ((msg[i] == 60 || msg[i] == 62) && quotes == 1)
			break ;
		if (msg[i] == 34 || msg[i] == 39)
		{
			if (msg[i] == type || type == 0)
			{
				type = msg[i];
				quotes = -quotes;
			}
		}
		i++;
	}
	op = init_op_struct(msg, i);
	return (op);
}

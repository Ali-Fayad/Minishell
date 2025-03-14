/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:27:31 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:06 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_here_docs(char *msg)
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
			count++;
		}
		else
			i++;
	}
	return (count);
}
typedef struct s_norminette_h
{
	char	*result;
	char	*temp;
	char	*rest;
	char	*new_result;
	char	*end;
	char	*end_s;
	char	*end_q;
	int		i;
	int		start;
}	t_norminette_h;

static void	update_result_and_index(t_norminette_h *norm)
{
	v_strcpy(norm->new_result, norm->temp);
	v_strcat(norm->new_result, "< tmp.txt ");
	v_strcat(norm->new_result, norm->rest);
	free(norm->temp);
	free(norm->rest);
	free(norm->result);
	free(norm->end_q);
	norm->result = norm->new_result;
	norm->i = norm->start + ft_strlen("< tmp.txt ");
}

static int	init_temp_rest_and_new_result(t_norminette_h *norm)
{
	norm->temp = ft_substr(norm->result, 0, norm->start);
	norm->rest = ft_substr(norm->result, norm->i,
			ft_strlen(norm->result) - norm->i);
	if (!norm->temp || !norm->rest)
		return (0);
	norm->new_result = malloc(ft_strlen(norm->temp)
			+ ft_strlen("< tmp.txt ") + ft_strlen(norm->rest) + 1);
	if (!norm->new_result)
		return (free(norm->temp), free(norm->rest), 0);
	return (1);
}

static int	process_heredoc(t_norminette_h *norm, int checker)
{
	norm->start = norm->i;
	norm->i += 2;
	while (norm->result[norm->i] && norm->result[norm->i] != '<'
		&& norm->result[norm->i] != '>')
		norm->i++;
	norm->end = ft_substr(norm->result, norm->start + 2,
			norm->i - norm->start - 2);
	if (!norm->end)
		return (0);
	norm->end_s = remove_spaces(norm->end);
	free(norm->end);
	if (!norm->end_s)
		return (0);
	norm->end_q = ft_quotes(norm->end_s);
	free(norm->end_s);
	if (!norm->end_q)
		return (0);
	if (checker == 1)
		here_doc2(norm->end_q);
	if (!init_temp_rest_and_new_result(norm))
		return (free(norm->end_q), 0);
	update_result_and_index(norm);
	return (1);
}

char	*split_heredoc_helper(char *msg, int checker)
{
	t_norminette_h	norm;

	norm.result = ft_strdup(msg);
	if (!norm.result)
		return (NULL);
	norm.i = 0;
	while (norm.result[norm.i])
	{
		if (norm.result[norm.i] == '<' && norm.result[norm.i + 1] == '<')
		{
			if (!process_heredoc(&norm, checker))
				return (free(norm.result), NULL);
		}
		else
			norm.i++;
	}
	return (norm.result);
}

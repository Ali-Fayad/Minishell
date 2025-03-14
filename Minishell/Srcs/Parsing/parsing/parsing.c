/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:42:19 by afayad            #+#    #+#             */
/*   Updated: 2025/03/12 21:57:08 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_pars	handle_allocation_failure(t_pars *q)
{
	if (q->open_q)
		free(q->open_q);
	if (q->close_q)
		free(q->close_q);
	q->open_q = NULL;
	q->close_q = NULL;
	return (*q);
}

static void	process_quotes(char *msg, t_pars *q, int *i, int *array)
{
	char	type;

	if (msg[*i] == 39 || msg[*i] == 34)
	{
		type = msg[*i];
		q->open_q[*array] = *i;
		(*i)++;
		while (msg[*i] != type && msg[*i])
			(*i)++;
		q->close_q[*array] = *i;
		(*array)++;
	}
}

t_pars	ft_pars(char *msg)
{
	t_pars	q;
	int		i;
	int		array;

	i = 0;
	array = 0;
	q.count = count_quotes(msg);
	if (q.count == -1)
	{
		q.open_q = NULL;
		q.close_q = NULL;
		return (q);
	}
	q.open_q = malloc(q.count * sizeof(int));
	q.close_q = malloc(q.count * sizeof(int));
	if (!q.open_q || !q.close_q)
		return (handle_allocation_failure(&q));
	while (msg[i])
	{
		process_quotes(msg, &q, &i, &array);
		i++;
	}
	return (q);
}

int	check_q(int i, t_pars new)
{
	int	j;

	if (new.open_q == NULL || new.close_q == NULL || new.count == 0)
		return (0);
	j = 0;
	while (j < new.count)
	{
		if (i == new.open_q[j] || i == new.close_q[j])
			return (1);
		j++;
	}
	return (0);
}
typedef struct s_norminette
{
	t_pars	new;
	char	*result;
	int		i;
	int		j;
}	t_norminette;

char	*ft_quotes(char *msg)
{
	t_norminette	norm;

	if (count_quotes(msg) == 0)
	{
		norm.result = ft_strdup(msg);
		return (norm.result);
	}
	norm.new = ft_pars(msg);
	norm.result = malloc((ft_strlen(msg) - count_quotes(msg) * 2 + 1));
	norm.i = 0;
	norm.j = 0;
	while (msg[norm.i])
	{
		if (check_q(norm.i, norm.new) == 0)
		{
			norm.result[norm.j] = msg[norm.i];
			norm.j++;
		}
		norm.i++;
	}
	norm.result[norm.j] = '\0';
	free(norm.new.close_q);
	free(norm.new.open_q);
	return (norm.result);
}

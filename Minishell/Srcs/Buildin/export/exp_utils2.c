/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:35:11 by afayad            #+#    #+#             */
/*   Updated: 2025/03/02 15:28:26 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_norminette
{
	int		word_count;
	int		i;
	int		j;
	int		word_start;
	int		quotes;
	char	type;
}	t_norminette;

static void	handle_quotes(char c, char *type, int *quotes)
{
	if (*type == 0)
	{
		*type = c;
		*quotes = 1;
	}
	else if (*type == c)
	{
		*type = 0;
		*quotes = -1;
	}
}

static int	handle_space(t_norminette *norm, char *msg, char **result)
{
	result[norm->j] = ft_substr(msg, norm->word_start,
			norm->i - norm->word_start);
	if (!result[norm->j])
		return (0);
	norm->j++;
	while (msg[norm->i] == 32)
		norm->i++;
	norm->word_start = norm->i;
	return (1);
}

static char	**init_export_split(t_norminette *norm, char *msg)
{
	char	**result;

	norm->word_count = export_split_helper(msg);
	result = (char **)malloc(sizeof(char *) * (norm->word_count + 1));
	if (!result)
		return (NULL);
	norm->i = 0;
	norm->j = 0;
	norm->quotes = -1;
	norm->type = 0;
	return (result);
}

static int	process_input_string3(t_norminette *norm, char *msg, char **result)
{
	while (msg[norm->i] != '\0')
	{
		if (msg[norm->i] == 34 || msg[norm->i] == 39)
			handle_quotes(msg[norm->i], &norm->type, &norm->quotes);
		if (msg[norm->i] == 32 && norm->quotes == -1)
		{
			if (!handle_space(norm, msg, result))
				return (0);
			continue ;
		}
		norm->i++;
	}
	return (1);
}

char	**export_split(char *msg)
{
	t_norminette	norm;
	char			**result;

	result = init_export_split(&norm, msg);
	if (!result)
		return (NULL);
	while (msg[norm.i] == 32)
		norm.i++;
	norm.word_start = norm.i;
	if (!process_input_string3(&norm, msg, result))
		return (free_env_array(result), NULL);
	if (msg[norm.word_start] != '\0')
	{
		result[norm.j] = ft_substr(msg, norm.word_start,
				norm.i - norm.word_start);
		if (!result[norm.j])
			return (free_env_array(result), NULL);
		norm.j++;
	}
	result[norm.j] = NULL;
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:10:48 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:10:48 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_exp *exp)
{
	if (exp == NULL)
		return ;
	if (exp->var)
		free(exp->var);
	if (exp->value)
		free(exp->value);
	free(exp);
}

void	ft_addvariable(t_env **head, char *variable)
{
	t_env	*new;
	t_env	*last;

	if (variable == NULL)
		return ;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	new->var = ft_strdup(variable);
	if (new->var == NULL)
	{
		free(new);
		return ;
	}
	new->check = 0;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

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
typedef struct s_norminette
{
	int		count;
	int		i;
	int		quotes;
	char	type;
}	t_norminette;

int	export_split_helper(char *msg)
{
	t_norminette	norm;

	norm.count = 0;
	norm.i = 0;
	norm.quotes = -1;
	norm.type = 0;
	while (msg[norm.i] != '\0')
	{
		if (msg[norm.i] == '"' || msg[norm.i] == '\'')
			handle_quotes(msg[norm.i], &norm.type, &norm.quotes);
		if (msg[norm.i] == ' ' && norm.quotes == -1)
		{
			while (msg[norm.i] == ' ')
				norm.i++;
			if (msg[norm.i] != '\0')
				norm.count++;
			continue ;
		}
		norm.i++;
	}
	if (msg[0] != '\0')
		norm.count++;
	return (norm.count);
}

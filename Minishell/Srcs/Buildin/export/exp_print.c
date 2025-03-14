/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:00:28 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:29 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_elements(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		if (current->check == 0)
			count++;
		current = current->next;
	}
	return (count);
}

char	**collect_vars(t_env *head, int count)
{
	char	**vars;
	t_env	*current;
	int		i;

	vars = malloc((count + 1) * sizeof(char *));
	if (vars == NULL)
		return (NULL);
	current = head;
	i = 0;
	while (current != NULL)
	{
		if (current->check == 0)
			vars[i++] = ft_strdup(current->var);
		current = current->next;
	}
	vars[i] = NULL;
	return (vars);
}

void	sort_vars(char **vars, int count)
{
	int		i;
	char	*temp;
	int		j;

	i = 1;
	while (i < count)
	{
		temp = vars[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(vars[j], temp) > 0)
		{
			vars[j + 1] = vars[j];
			j--;
		}
		vars[j + 1] = temp;
		i++;
	}
}

void	print_vars(char **vars, int count)
{
	int		i;
	char	*equal;
	int		j;

	i = 0;
	while (i < count)
	{
		equal = NULL;
		write(1, "declare -x ", 11);
		j = 0;
		while (vars[i][j] != '\0')
		{
			write(1, &vars[i][j], 1);
			if (vars[i][j++] == '=' && equal == NULL)
			{
				write(1, "\"", 1);
				equal = "";
			}
		}
		if (equal != NULL)
			write(1, "\"", 1);
		write(1, "\n", 1);
		free(vars[i]);
		i++;
	}
}

void	print_export(t_env *head)
{
	int		count;
	char	**vars;

	count = count_elements(head);
	if (count == 0)
	{
		printf("No variables to export.\n");
		return ;
	}
	vars = collect_vars(head, count);
	if (vars == NULL)
	{
		printf("Allocation failed\n");
		exit(1);
	}
	sort_vars(vars, count);
	print_vars(vars, count);
	free(vars);
}

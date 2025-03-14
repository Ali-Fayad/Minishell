/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:07:05 by afayad            #+#    #+#             */
/*   Updated: 2025/02/22 05:07:05 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_null_null(t_env **head)
{
	t_env	*current;
	char	*result;

	current = *head;
	result = NULL;
	while (current)
	{
		if (ft_strncmp(current->var, "HOME=", 5) == 0)
			result = ft_strdup(current->var + 5);
		current = current->next;
	}
	if (result)
	{
		if (chdir(result) == -1)
			perror("chdir");
		change_env(head, "PWD=", result);
		free(result);
	}
}

int	search_env_var(t_env **head, char *search)
{
	t_env	*current;

	current = *head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->var, search, ft_strlen(search))
			&& current->var[ft_strlen(search)] == '=')
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}
// for norminette

static int	filter_tokens(char **tokens, char **stack)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "..") == 0)
		{
			if (n > 0)
				--n;
		}
		else if (ft_strcmp(tokens[i], ".") != 0)
			stack[n++] = tokens[i];
		++i;
	}
	return (n);
}

char	*remove_dot_segments(char *direction)
{
	char	**stack;
	char	**tokens;
	char	*result;
	int		n;
	int		i;

	tokens = ft_split(direction, '/');
	stack = (char **)malloc(strlen(direction) * sizeof(char *));
	n = filter_tokens(tokens, stack);
	result = (char *)malloc(strlen(direction) + 2);
	result[0] = '/';
	result[1] = '\0';
	i = 0;
	while (i < n)
	{
		v_strcat(result, stack[i]);
		if (i < n - 1)
			v_strcat(result, "/");
		++i;
	}
	free(stack);
	free_env_array(tokens);
	return (result);
}

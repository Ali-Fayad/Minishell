/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:06:58 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:25 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_norminette
{
	int		i;
	t_env	*current;
	t_env	*new_node;
}	t_norminette;

void	add_env(char **envp, t_env **head)
{
	t_norminette	norm;

	norm.i = 0;
	if (envp[norm.i] == NULL)
		handle_empty_env(head);
	while (envp[norm.i] != NULL)
	{
		norm.new_node = malloc(sizeof(t_env));
		norm.new_node->var = ft_strdup(envp[norm.i]);
		if (norm.new_node->var == NULL)
			return (free(norm.new_node), free_env(*head));
		norm.new_node->check = 0;
		norm.new_node->next = NULL;
		if (*head == NULL)
			*head = norm.new_node;
		else
		{
			norm.current = *head;
			while (norm.current->next != NULL)
				norm.current = norm.current->next;
			norm.current->next = norm.new_node;
		}
		norm.i++;
	}
}

void	print_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strchr(current->var, '=') && current->check == 0)
			printf("%s\n", current->var);
		current = current->next;
	}
}

void	change_env(t_env **head, char *catch, char *replace)
{
	t_env	*current;
	char	*new_var;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->var, catch, ft_strlen(catch)) == 0)
		{
			new_var = ft_strjoin(catch, replace);
			if (!new_var)
				return ;
			if (ft_strcmp(current->var, new_var) != 0)
			{
				free(current->var);
				current->var = new_var;
			}
			else
				free(new_var);
			current->check = 0;
			return ;
		}
		current = current->next;
	}
}

void	free_env(t_env *head)
{
	t_env	*current;
	t_env	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->var);
		free(current);
		current = next_node;
	}
}

void	increment_shlvl(t_env **head)
{
	char	*shlvl_value;
	int		shlvl_int;
	char	*shlvl_str;
	char	*fullvar;

	shlvl_value = get_env_value("SHLVL", head);
	if (!shlvl_value)
		shlvl_value = "0";
	shlvl_int = ft_atoi(shlvl_value);
	shlvl_int++;
	shlvl_str = ft_itoa(shlvl_int);
	fullvar = ft_strjoin("SHLVL=", shlvl_str);
	update_variable(head, "SHLVL", fullvar);
	free(shlvl_str);
	free(fullvar);
}

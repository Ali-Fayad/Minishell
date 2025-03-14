/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:56:59 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:41 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_env **head)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		buf = get_env_value("PWD", head);
	change_env(head, "PWD=", buf);
	change_check("PWD=", head, 0);
	printf("%s\n", buf);
	free(buf);
}

int	ft_isvar(char *var, int *exit_status)
{
	int	i;
	int	result;

	result = 1;
	if (!(var[0] >= 'a' && var[0] <= 'z')
		&& !(var[0] >= 'A' && var[0] <= 'Z') && var[0] != '_')
		result = 0;
	i = 1;
	while (var[i] != '\0')
	{
		if (!(var[i] >= 'a' && var[i] <= 'z')
			&& !(var[i] >= 'A' && var[i] <= 'Z')
			&& !(var[i] >= '0' && var[i] <= '9') && var[i] != '_')
			result = 0;
		i++;
	}
	if (result == 0)
		print_error("Shell: variable format is not valid!\n", 1, exit_status);
	return (result);
}

void	change_check(char *var, t_env **head, int new)
{
	t_env	*current;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var, ft_strlen(var)) == 0)
		{
			current->check = new;
			return ;
		}
		current = current->next;
	}
}

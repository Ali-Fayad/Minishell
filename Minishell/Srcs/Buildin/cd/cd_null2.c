/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_null2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:20:34 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home_or_null(char *current, char *result, t_env **head)
{
	if (!ft_strcmp(result, "cd") || !ft_strcmp(result, "cd ~"))
	{
		cd_null_null(head);
		change_env(head, "OLDPWD=", current);
	}
}

static void	cd_oldpwd(char *current, char *prev, t_env **head)
{
	if (!ft_strcmp(prev, "cd -"))
	{
		if (search_env_var(head, "OLDPWD") == 1)
		{
			if (chdir(prev) == -1)
				perror("chdir");
			else
			{
				change_env(head, "OLDPWD=", current);
				change_env(head, "PWD=", prev);
			}
		}
		else
			printf("Shell: there is no OLDPWD!\n");
	}
}

static void	cd_parent_dir(char *current, t_env **head)
{
	char	*new_path;

	new_path = ft_strcat(current, "/..");
	printf("without ,, : %s\n", remove_dot_segments(new_path));
	if (chdir(remove_dot_segments(new_path)) == -1)
	{
		perror("chdir");
		change_env(head, "OLDPWD=", current);
		change_env(head, "PWD=", new_path);
	}
	free(new_path);
}

void	no_dir(char *msg, t_env **head)
{
	char	*current;
	char	*result;
	char	*prev;

	current = get_env_value("PWD", head);
	result = remove_spaces(msg);
	prev = get_env_value("OLDPWD", head);
	cd_home_or_null(current, result, head);
	cd_oldpwd(current, result, head);
	if (!ft_strcmp(result, "cd .."))
		cd_parent_dir(current, head);
	free(result);
	free(current);
	free(prev);
}

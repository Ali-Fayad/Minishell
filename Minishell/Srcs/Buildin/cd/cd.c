/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:48:59 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_dir(int *g_exit_status)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		print_error("cd: error retrieving current directory\n",
			0, g_exit_status);
		return (NULL);
	}
	return (current);
}

// nrominette helpers

static void	handle_parent_directory(t_env **head, char *full_path,
	int *g_exit_status)
{
	char	*reduced_path;

	reduced_path = r_l_b(full_path);
	if (!reduced_path)
	{
		print_error("cd: Allocation failed\n", 1, g_exit_status);
		return ;
	}
	change_env(head, "PWD=", reduced_path);
	free(reduced_path);
}

static void	cd_to_path(t_env **head, char *new_path, char *current,
	int *g_exit_status)
{
	char	*full_path;

	full_path = malloc(strlen(current) + strlen(new_path) + 2);
	v_strcpy(full_path, current);
	v_strcat(full_path, "/");
	v_strcat(full_path, new_path);
	if (chdir(full_path) != 0)
	{
		printf("cd: %s: No such file or directory\n", new_path);
		*g_exit_status = 1;
		free(full_path);
		return ;
	}
	change_env(head, "OLDPWD=", current);
	if (!ft_strcmp(new_path, ".."))
	{
		handle_parent_directory(head, full_path, g_exit_status);
	}
	else
	{
		change_env(head, "PWD=", full_path);
	}
	*g_exit_status = 0;
	free(full_path);
}

// end

static int	cd_special_cases(t_env **head, char *msg, char *current)
{
	char	*new_path;

	if (ft_strlen(msg) > 3)
		new_path = ft_strskip(msg, 3);
	else
		new_path = remove_spaces(msg);
	if (!new_path || ft_strcmp(new_path, "~") == 0 || ft_strcmp(msg, "cd") == 0)
	{
		cd_null(head);
		change_env(head, "OLDPWD=", current);
		free(new_path);
		return (1);
	}
	if (ft_strcmp(new_path, "-") == 0)
	{
		if (get_oldpwd(head) == 1)
		{
			change_env(head, "OLDPWD=", current);
			pwd(head);
		}
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

void	cd(char *msg, t_env **head, int *g_exit_status)
{
	char	*current;
	char	*new_path;

	current = get_current_dir(g_exit_status);
	if (!current)
	{
		no_dir(msg, head);
		return ;
	}
	if (cd_special_cases(head, msg, current) == 0)
	{
		new_path = ft_strskip(msg, 2);
		if (new_path)
		{
			if (msg[2] != ' ')
			{
				printf("command not found!\n");
				free(current);
				return ;
			}
			cd_to_path(head, new_path, current, g_exit_status);
			free(new_path);
		}
	}
	free(current);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:23:08 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:21 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*r_l_b(char *str)
{
	char	*last_slash;
	char	*result;
	size_t	length;

	if (!str)
		return (NULL);
	last_slash = ft_strrchr(str, '/');
	if (last_slash != NULL)
	{
		length = last_slash - str;
		result = malloc(length + 1);
		if (!result)
			return (NULL);
		ft_strncpy(result, str, length);
		result[length] = '\0';
	}
	else
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		*result = '\0';
	}
	return (result);
}

// norminette helperss

static int	change_directory_and_update_oldpwd(char *oldpwd, t_env **head)
{
	char	*cwd;

	if (chdir(oldpwd) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("getcwd");
			return (0);
		}
		change_env(head, "PWD=", cwd);
		free(cwd);
		return (1);
	}
	printf("Shell : %s is not a directory\n", oldpwd);
	return (0);
}

int	get_oldpwd(t_env **head)
{
	t_env	*current;
	char	*oldpwd;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->var, "OLDPWD=", 7) == 0)
		{
			if (current->check == 1)
			{
				printf("Shell : OLDPWD is not founded!\n");
				return (0);
			}
			oldpwd = ft_strchr(current->var, '=') + 1;
			if (oldpwd)
				return (change_directory_and_update_oldpwd(oldpwd, head));
		}
		current = current->next;
	}
	printf("Shell : OLDPWD is not founded!\n");
	return (0);
}

// end

// norminette helpers

static void	change_directory_and_update_pwd(char *result, t_env **head)
{
	char	*pwd;

	if (chdir(result) == -1)
		perror("chdir");
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		change_env(head, "PWD=", pwd);
		free(pwd);
	}
}

void	cd_null(t_env **head)
{
	t_env	*current;
	char	*result;

	result = NULL;
	current = *head;
	while (current)
	{
		if (ft_strncmp(current->var, "HOME=", 5) == 0)
		{
			result = ft_strdup(current->var + 5);
			if (!result)
				return ;
		}
		current = current->next;
	}
	if (result)
	{
		change_directory_and_update_pwd(result, head);
		free(result);
	}
}

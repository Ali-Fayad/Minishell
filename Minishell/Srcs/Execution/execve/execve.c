/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:37:54 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:55 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_in_env(t_env *head)
{
	while (head)
	{
		if (ft_strnstr(head->var, "PATH=", 5) == 0)
			if (head->check == 0)
				return (head->var + 5);
		head = head->next;
	}
	return (NULL);
}

char	*join_and_check_path(char *part_path, char *cmd)
{
	char	*path;

	path = ft_strjoin(part_path, cmd);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	*check_paths(char **paths, char *cmd)
{
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (NULL);
		path = join_and_check_path(part_path, cmd);
		free(part_path);
		if (path)
			return (path);
		i++;
	}
	return (NULL);
}

char	*g_path(char *cmd, t_env *head)
{
	char	**paths;
	char	*path;
	int		i;
	char	*stripped_cmd;

	stripped_cmd = strip_dot_slash(cmd);
	if (stripped_cmd)
		return (stripped_cmd);
	paths = ft_split(find_path_in_env(head), ':');
	if (!paths)
		return (NULL);
	path = check_paths(paths, cmd);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (path);
}

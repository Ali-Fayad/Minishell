/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:33:05 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:53 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child(char **cmd, t_env *head, int *g_exit_status)
{
	char	*path;
	char	**env_array;

	restore_signals();
	increment_shlvl(&head);
	path = g_path(cmd[0], head);
	if (!path)
	{
		print_error("Shell: Command not found\n", 127, g_exit_status);
		exit(127);
	}
	env_array = transfer_to_2d_array(head);
	if (execve(path, cmd, env_array) == -1)
	{
		print_error("execve error!\n", 1, g_exit_status);
		free_env_array(env_array);
		exit(1);
	}
	free_env_array(env_array);
}

static void	handle_parent(pid_t pid, int *g_exit_status)
{
	int	status;

	ignore_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		*g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			*g_exit_status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			*g_exit_status = 131;
		else
			*g_exit_status = 128 + WTERMSIG(status);
	}
}

void	execute_command(char *arg, t_env *head, int *g_exit_status)
{
	char	**cmd;
	pid_t	pid;

	cmd = ft_split(arg, ' ');
	if (!cmd || !cmd[0])
	{
		free(cmd);
		return (print_error("Shell: Command not found\n", 127, g_exit_status));
	}
	pid = fork();
	if (pid == 0)
		handle_child(cmd, head, g_exit_status);
	else
		handle_parent(pid, g_exit_status);
	free_env_array(cmd);
}

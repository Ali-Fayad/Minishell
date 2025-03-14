/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:03:10 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:57 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredocs_child(t_pipe *pipe_data)
{
	restore_signals();
	pipe_data->cmds = process_heredocs_with_copy(pipe_data->raw_cmds, 1);
	if (pipe_data->cmds)
		free_cmds(pipe_data->cmds, pipe_data->num_pipes + 1);
	free_cmds(pipe_data->raw_cmds, pipe_data->num_pipes + 1);
	exit(0);
}

void	handle_child_process(t_pipe *pipe_data, t_env **head,
	int *g_exit_status)
{
	restore_signals();
	if (pipe_data->prev_fd != -1)
	{
		dup2(pipe_data->prev_fd, STDIN_FILENO);
		close(pipe_data->prev_fd);
	}
	if (pipe_data->cmds[pipe_data->cmd_index + 1])
	{
		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
		close(pipe_data->pipe_fd[1]);
	}
	close(pipe_data->pipe_fd[0]);
	ft_check2(pipe_data->cmds[pipe_data->cmd_index], head, g_exit_status);
	exit(*g_exit_status);
}

void	execute_commands(t_pipe *pipe_data, t_env **head,
		int *g_exit_status)
{
	while (pipe_data->cmds[pipe_data->cmd_index])
	{
		if (pipe_data->cmds[pipe_data->cmd_index + 1]
			&& pipe(pipe_data->pipe_fd) == -1)
		{
			perror("pipe");
			break ;
		}
		pipe_data->exec_data.i = pipe_data->cmd_index;
		pipe_data->exec_data.pids[pipe_data->cmd_index] = fork();
		if (pipe_data->exec_data.pids[pipe_data->cmd_index] == 0)
		{
			handle_child_process(pipe_data, head, g_exit_status);
		}
		if (pipe_data->prev_fd != -1)
			close(pipe_data->prev_fd);
		if (pipe_data->cmds[pipe_data->cmd_index + 1])
			close(pipe_data->pipe_fd[1]);
		pipe_data->prev_fd = pipe_data->pipe_fd[0];
		pipe_data->cmd_index++;
	}
}

void	wait_for_children(t_pipe *pipe_data, int *g_exit_status)
{
	pipe_data->i = 0;
	while (pipe_data->i < pipe_data->num_pipes + 1)
	{
		waitpid(pipe_data->exec_data.pids[pipe_data->i], &pipe_data->status, 0);
		if (WIFEXITED(pipe_data->status))
			*g_exit_status = WEXITSTATUS(pipe_data->status);
		pipe_data->i++;
	}
}

void	handle_heredoc_failure(t_pipe *pipe_data, int *g_exit_status)
{
	free_cmds(pipe_data->raw_cmds, pipe_data->num_pipes + 1);
	free(pipe_data->msg);
	if (WIFSIGNALED(pipe_data->status))
		*g_exit_status = 130;
	write(1, "\n", 1);
}

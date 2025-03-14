/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:06:32 by afayad            #+#    #+#             */
/*   Updated: 2025/03/12 22:21:20 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_finalize(t_pipe *pipe_data, int *g_exit_status)
{
	wait_for_children(pipe_data, g_exit_status);
	free(pipe_data->exec_data.pids);
	free_cmds(pipe_data->cmds, pipe_data->num_pipes + 1);
	free(pipe_data->msg);
	setup_signals();
}

int	handle_heredoc_process(t_pipe *pipe_data, int *g_exit_status)
{
	pipe_data->heredoc_pid = fork();
	if (pipe_data->heredoc_pid == 0)
		process_heredocs_child(pipe_data);
	waitpid(pipe_data->heredoc_pid, &pipe_data->status, 0);
	ignore_signals();
	if (WIFSIGNALED(pipe_data->status) || WEXITSTATUS(pipe_data->status) != 0)
	{
		handle_heredoc_failure(pipe_data, g_exit_status);
		return (0);
	}
	return (1);
}

void	ft_pipe(char *cmd, t_env **head, int *g_exit_status)
{
	t_pipe	pipe_data;

	pipe_data.msg = ft_valid(cmd, head, g_exit_status);
	if (!pipe_data.msg)
		return ;
	pipe_data.num_pipes = count_pipe(pipe_data.msg);
	if (pipe_data.num_pipes == 0)
		return ((ft_check2(pipe_data.msg, head, g_exit_status)),
			(free(pipe_data.msg)));
	pipe_data.raw_cmds = spliting_pipe(pipe_data.msg);
	if (!handle_heredoc_process(&pipe_data, g_exit_status))
		return ;
	pipe_data.cmds = process_heredocs_with_copy(pipe_data.raw_cmds, 0);
	free_cmds(pipe_data.raw_cmds, pipe_data.num_pipes + 1);
	if (!pipe_data.cmds)
		return (free(pipe_data.msg));
	pipe_data.exec_data.g_exit_status = *g_exit_status;
	pipe_data.exec_data.head = head;
	pipe_data.exec_data.pids = malloc(sizeof(pid_t)
			* (pipe_data.num_pipes + 1));
	pipe_data.prev_fd = -1;
	pipe_data.cmd_index = 0;
	execute_commands(&pipe_data, head, g_exit_status);
	cleanup_and_finalize(&pipe_data, g_exit_status);
}

int	count_pipe(char *msg)
{
	int		i;
	char	type;
	int		quotes;
	int		count;

	i = 0;
	quotes = 1;
	count = 0;
	type = 9;
	while (msg[i])
	{
		if (msg[i] == 34 || msg[i] == 39)
		{
			if (type == 9 || type == msg[i])
			{
				quotes = -quotes;
				type = msg[i];
			}
		}
		if (msg[i] == '|' && quotes == 1)
			count++;
		i++;
	}
	return (count);
}

char	**spliting_pipe(char *msg)
{
	t_splitting_pipe	norm;

	if (!init_splitting_pipe(&norm, msg))
		return (NULL);
	if (!process_input_string2(&norm, msg))
	{
		free(norm.args);
		free(norm.tmp);
		return (NULL);
	}
	if (norm.tmp)
	{
		norm.args[norm.k] = ft_strndup(norm.tmp, norm.j);
		if (!norm.args[norm.k])
		{
			free(norm.args);
			free(norm.tmp);
			return (NULL);
		}
		norm.k++;
	}
	norm.args[norm.k] = NULL;
	free(norm.tmp);
	return (norm.args);
}

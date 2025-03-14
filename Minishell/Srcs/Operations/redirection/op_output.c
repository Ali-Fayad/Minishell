/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:45:20 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:18 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_op2(char *tmp, int *exit_status, int count)
{
	if (count == 1)
		dir_output(tmp, 0, exit_status);
	else
		dir_output(tmp, 1, exit_status);
}

void	dir_output(const char *filename, int append, int *g_exit_status)
{
	int	fd;
	int	flags;

	if (filename == NULL)
		filename = "/dev/null";
	if (append == 0)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (append == 1)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		if (filename[0] == '/' && filename[1] == '\0')
			print_error("Shell: %s is a Directory\n", 2, g_exit_status);
		else
			print_error("Shell: Error redirecting output\n", 2, g_exit_status);
		exit(*g_exit_status);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		print_error("Shell: Error redirecting output\n", 2, g_exit_status);
		close(fd);
		exit(*g_exit_status);
	}
	close(fd);
}

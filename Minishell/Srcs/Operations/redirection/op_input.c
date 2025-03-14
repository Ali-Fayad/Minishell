/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:43:06 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:02:01 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_process(char *processed_result, int count, int *g_exit_status)
{
	if (processed_result == NULL)
	{
		printf("Error: memory allocation failed\n");
		return ;
	}
	if (count == 1)
		dir_input(processed_result, g_exit_status);
	else if (count == 2)
		dir_input("tmp.txt", g_exit_status);
	else
	{
		print_error("Error: invalid input redirection\n", 1, g_exit_status);
	}
}

void	input_op2(char *tmp, int *exit_status, int count)
{
	if (count == 1)
		dir_input(tmp, exit_status);
	else
		dir_input("tmp.txt", exit_status);
}

void	dir_input(const char *filename, int *g_exit_status)
{
	int	fd;

	if (filename == NULL)
		filename = "/dev/null";
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Shell: Error opening file for input redirection\n",
			2, g_exit_status);
		exit(*g_exit_status);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		print_error("Shell: Error redirecting input\n", 2, g_exit_status);
		close(fd);
		exit(*g_exit_status);
	}
	close(fd);
}

int	op_first(char *msg)
{
	if (msg[0] == '<' || msg[0] == '>')
		return (1);
	return (0);
}

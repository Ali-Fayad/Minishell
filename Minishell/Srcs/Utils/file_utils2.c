/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:10:32 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:56 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_chars_to_file(const char *filename, char *str)
{
	int		fd;
	ssize_t	bytes_written;
	char	*current_char;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
		return (perror("Error opening file"));
	current_char = str;
	while (*current_char != '\0')
	{
		bytes_written = write(fd, current_char, 1);
		if (bytes_written == -1)
		{
			perror("Error writing to file");
			close(fd);
			return ;
		}
		++current_char;
	}
	if (str[strlen(str) - 1] != '\n')
		write(fd, "\n", 1);
	if (close(fd) == -1)
		perror("Error closing file");
}

void	clear_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	if (close(fd) == -1)
		perror("Error closing file");
}

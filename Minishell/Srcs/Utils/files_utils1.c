/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:05:51 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:01 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countfile(char *filename)
{
	char	c;
	int		count;
	int		fd;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (read(fd, &c, 1) > 0)
		count++;
	close(fd);
	return (count);
}

static char	*array_in(char *filename)
{
	char	*file;
	char	c;
	int		fd;
	int		i;
	int		file_size;

	file_size = ft_countfile(filename);
	file = malloc((file_size + 1) * sizeof(char));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	i = 0;
	while (read(fd, &c, 1) > 0)
	{
		file[i] = c;
		i++;
	}
	file[i] = '\0';
	close(fd);
	return (file);
}

void	dup_file(char *filein, char *fileout)
{
	int		fd;
	int		file_size;
	char	*file;

	file = array_in(filein);
	if (file == NULL)
		return ;
	file_size = 0;
	while (file[file_size] != '\0')
		file_size++;
	fd = open(fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(file);
		return ;
	}
	write(fd, file, file_size);
	close(fd);
	free(file);
}

void	write_to_file(char *buf)
{
	int		fd2;
	ssize_t	bytes_written;
	size_t	len;

	if (buf == NULL)
	{
		write(STDERR_FILENO, "Error: Buffer is NULL\n", 22);
		return ;
	}
	fd2 = open("pwd2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		perror("Error opening file");
		return ;
	}
	len = 0;
	while (buf[len] != '\0')
		len++;
	bytes_written = write(fd2, buf, len);
	printf("%s\n", buf);
	if (bytes_written == -1)
		perror("Error writing to file");
	close(fd2);
}

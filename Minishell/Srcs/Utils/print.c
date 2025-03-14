/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:09:43 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:01:26 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *message, int exit, int *g_exit_status)
{
	if (message != NULL)
		write(2, message, ft_strlen(message));
	*g_exit_status = exit;
}

void	print_error_arg(char *message, char *var, int exit, int *g_exit_status)
{
	if (message != NULL && var != NULL)
	{
		write(2, var, ft_strlen(var));
		write(2, " :", 2);
		write(2, message, ft_strlen(message));
	}
	*g_exit_status = exit;
}

void	print_exit(char *msg, int exit_code)
{
	write(2, msg, ft_strlen(msg));
	exit(exit_code);
}

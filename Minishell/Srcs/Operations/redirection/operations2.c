/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:51:01 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:23 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*operations(char *msg, int *g_exit_status)
{
	t_op	result;

	result = op_extract_command(msg);
	op_redirection(result.second, g_exit_status);
	if (result.second != NULL)
		free(result.second);
	return (result.first);
}

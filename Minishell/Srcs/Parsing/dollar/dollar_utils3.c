/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:25:42 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:36 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_char(t_dollar *dollar, char *input)
{
	if (input[dollar->i] == 34 && dollar->quotes2 == -1)
		dollar->result[dollar->j++] = '$';
	else
		dollar->result[dollar->j++] = '$';
	if (input[dollar->i] != ' ' && input[dollar->i] != '\0')
		dollar->result[dollar->j++] = input[dollar->i++];
}

int	should_process_dollar(t_dollar *dollar, char *input)
{
	return (input[dollar->i] == '$'
		&& (dollar->quotes == 1 || (dollar->quotes2 == -1
				&& dollar->quotes == -1))
		&& (dollar->i == 0 || input[dollar->i - 1] != 92));
}

int	process_dollar_logic(t_dollar *dollar, char *input, t_env **head,
		int *g_exit_status)
{
	if (is_special_char(input[dollar->i + 1]))
	{
		dollar->i++;
		if (input[dollar->i] == '?')
		{
			if (!handle_exit_status(dollar, g_exit_status))
				return (0);
		}
		else
			handle_dollar_char(dollar, input);
	}
	else if (ft_isalpha(input[dollar->i + 1]) == 0
		&& input[dollar->i + 1] != '_')
		dollar->i += 2;
	else
		handle_env_var(dollar, input, head, g_exit_status);
	return (1);
}

int	process_input_string(t_dollar *dollar, char *input, t_env **head,
	int *g_exit_status)
{
	while (dollar->i < dollar->len)
	{
		if (input[dollar->i] == 39)
			dollar->quotes = -dollar->quotes;
		if (input[dollar->i] == 34)
			dollar->quotes2 = -dollar->quotes2;
		if (input[dollar->i] == 92)
			dollar->i++;
		if (should_process_dollar(dollar, input))
		{
			if (!process_dollar_logic(dollar, input, head, g_exit_status))
				return (0);
		}
		else
			dollar->result[dollar->j++] = input[dollar->i++];
	}
	return (1);
}

int	handle_exit_status(t_dollar *dollar, int *g_exit_status)
{
	dollar->exit_str = ft_itoa(*g_exit_status);
	if (!dollar->exit_str)
		return (0);
	dollar->exit_len = ft_strlen(dollar->exit_str);
	if (dollar->j + dollar->exit_len < dollar->result_len - 1)
	{
		ft_memcpy(&dollar->result[dollar->j],
			dollar->exit_str, dollar->exit_len);
		dollar->j += dollar->exit_len;
	}
	free(dollar->exit_str);
	dollar->i++;
	return (1);
}

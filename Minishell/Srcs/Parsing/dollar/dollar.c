/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:04:27 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:38 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name_after_dollar2(char *input, int *i)
{
	int	len;

	len = 0;
	if (ft_isdigit(input[*i + 1]) == 1)
	{
		(*i)++;
		return (char_to_string(input[*i]));
	}
	(*i)++;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	if (len == 0)
		len = 1;
	return (ft_substr(input, *i - len, len));
}

void	handle_env_var(t_dollar *dollar, char *input, t_env **head,
		int *g_exit_status)
{
	dollar->var_name = get_var_name_after_dollar2(input, &dollar->i);
	if (dollar->var_name)
	{
		dollar->env_value = find_env_var(dollar->var_name, head, g_exit_status);
		free(dollar->var_name);
		if (dollar->env_value)
		{
			while (*dollar->env_value)
				dollar->result[dollar->j++] = *dollar->env_value++;
		}
		else if (input[dollar->i] != '\0')
			dollar->result[dollar->j++] = input[dollar->i++];
	}
	else
	{
		dollar->i++;
		if (input[dollar->i] != '\0')
			dollar->result[dollar->j++] = input[dollar->i++];
	}
}

int	is_special_char(char c)
{
	return (c == ' ' || c == '\0' || c == '%' || c == '+' || c == '-'
		|| c == ':' || c == '=' || c == '?' || c == '"' || c == '\'');
}

char	*replace_env_varss(char *input, t_env **head, int *g_exit_status)
{
	t_dollar	dollar;

	dollar.len = ft_strlen(input);
	dollar.result_len = dollar_counter(input, head);
	dollar.result = (char *)malloc(dollar.result_len);
	if (!dollar.result)
		return (NULL);
	dollar.i = 0;
	dollar.j = 0;
	dollar.quotes = 1;
	dollar.quotes2 = 1;
	if (!process_input_string(&dollar, input, head, g_exit_status))
		return (NULL);
	dollar.result[dollar.j] = '\0';
	return (dollar.result);
}

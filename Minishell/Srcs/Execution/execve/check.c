/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:48:44 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:47 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces(char *str)
{
	int		start;
	int		end;
	int		i;
	char	*new_str;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] == ' ' && str[start] != '\0')
		start++;
	while (end >= start && str[end] == ' ')
		end--;
	new_str = (char *)malloc((end - start + 2) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		new_str[i] = str[start];
		start++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	command_menu(char *result, t_env **head, int *g_exit_status)
{
	char	*quotes;
	char	*quotes_s;

	quotes = ft_quotes(result);
	quotes_s = remove_spaces(quotes);
	if (ft_strcmp(quotes, "pwd") == 0)
		pwd(head);
	else if (ft_strncmp(quotes, "cd", 2) == 0)
		cd(quotes, head, g_exit_status);
	else if (ft_strcmp(quotes, "env") == 0)
		print_env(*head);
	else if (ft_strncmp(quotes, "echo ", 5) == 0)
		echo(quotes, g_exit_status);
	else if (ft_strncmp(quotes, "unset", 5) == 0)
		unset(head, quotes);
	else if (ft_strncmp(quotes, "export", 6) == 0)
		export(result, head, g_exit_status);
	else if (ft_strncmp(quotes_s, "exit", 4) == 0)
		ft_exit(quotes_s, g_exit_status);
	else
		execute_command(quotes, *head, g_exit_status);
	free(quotes);
	free(quotes_s);
}

//norminette helpers

static void	fork_and_execute_command(char *result, t_env **head,
	int *g_exit_status)
{
	int		pid;
	char	*command_result;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		restore_signals();
		command_result = operations(result, g_exit_status);
		if (command_result != NULL)
			command_menu(command_result, head, g_exit_status);
		exit(*g_exit_status);
	}
	else
	{
		ignore_signals();
		wait(&status);
		setup_signals();
		if (WIFEXITED(status))
			*g_exit_status = WEXITSTATUS(status);
	}
}

void	ft_check2(char *msg, t_env **head, int *g_exit_status)
{
	char	*result;

	result = ft_strdup(msg);
	if (catch_op(result) > -1)
		fork_and_execute_command(result, head, g_exit_status);
	else
		command_menu(result, head, g_exit_status);
	free(result);
}

// end

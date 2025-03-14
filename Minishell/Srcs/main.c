/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:37:10 by afayad            #+#    #+#             */
/*   Updated: 2025/03/12 21:22:26 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_s;

void	handle_empty_env(t_env **head)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		pwd_var = malloc(strlen(pwd) + 5);
		if (pwd_var)
		{
			strcpy(pwd_var, "PWD=");
			strcat(pwd_var, pwd);
			ft_addvariable(head, pwd_var);
			free(pwd_var);
		}
		free(pwd);
	}
	ft_addvariable(head, "OLDPWD");
	ft_addvariable(head, "SHLVL=1");
}

typedef struct s_norminette
{
	int		in_quotes;
	char	quote_char;
}	t_norminette;

int	check_space_in_quotes(const char *str)
{
	t_norminette	norm;

	norm.in_quotes = 0;
	norm.quote_char = 0;
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && !norm.in_quotes)
		{
			norm.in_quotes = 1;
			norm.quote_char = *str;
		}
		else if (*str == norm.quote_char && norm.in_quotes)
		{
			norm.in_quotes = 0;
			norm.quote_char = 0;
		}
		else if (*str == ' ' && norm.in_quotes)
			return (1);
		else if (*str == ' ' && !norm.in_quotes)
			return (0);
		str++;
		if (!norm.in_quotes && *str == ' ')
			break ;
	}
	return (0);
}

static void	handle_exit_command(char *input, char *quoted_input,
		int *g_exit_status)
{
	if (ft_exit(quoted_input, g_exit_status))
	{
		free(input);
		free(quoted_input);
		printf("exit\n");
		exit(*g_exit_status);
	}
}

void	process_input(char *input, t_env **head, int *g_exit_status)
{
	char	*quoted_input;
	char	*spaces_removed;

	if (!input)
	{
		printf("exit\n");
		exit(*g_exit_status);
	}
	quoted_input = ft_quotes(input);
	handle_exit_command(input, quoted_input, g_exit_status);
	if (*input && !is_only_spaces(input))
		add_history(input);
	else if (is_only_spaces(input) || *input == '\n')
		return (free(input), free(quoted_input));
	spaces_removed = remove_spaces(input);
	if (!check_space_in_quotes(spaces_removed))
		ft_pipe(input, head, g_exit_status);
	else
		print_error("Command Not Found!\n", 27, g_exit_status);
	free(input);
	free(quoted_input);
	free(spaces_removed);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*head;
	int		g_exit_status;

	(void)ac;
	(void)av;
	head = NULL;
	add_env(envp, &head);
	setup_signals();
	g_exit_status = 0;
	while (1)
	{
		input = readline("\033[1m\033[31mMinishell% \033[36m");
		if (g_s == 2 || g_s == 3)
		{
			g_exit_status = 128 + g_s;
			g_s = 0;
		}
		process_input(input, &head, &g_exit_status);
	}
	free_env(head);
	return (g_exit_status);
}

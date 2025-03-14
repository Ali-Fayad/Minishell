/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:03:46 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:00:47 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verify_slash(char *msg)
{
	int		i;
	int		j;
	char	*result;
	int		len;
	int		backslash_count;

	len = ft_strlen(msg);
	backslash_count = ft_count_char(msg, 92);
	result = malloc(len - backslash_count + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (msg[i])
	{
		if (msg[i] == 92)
		{
			i++;
			continue ;
		}
		result[j++] = msg[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	ends_with_redirect(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	if (len == 0)
		return (0);
	return (msg[len - 1] == '>' || msg[len - 1] == '<');
}

static int	ft_isdirec(char *result, int *exit_status)
{
	if (result[0] == 38)
	{
		print_error("Shell: syntax error near unexpected token `&'\n",
			126, exit_status);
		return (1);
	}
	if (is_first_word_directory(result) == 1)
	{
		print_error("Shell : it's a Directory\n", 126, exit_status);
		return (1);
	}
	return (0);
}

int	valid_util(char *result, int *exit_status)
{
	if (!result)
		return (0);
	if (result[0] == '|' || result[ft_strlen(result) - 1] == '|')
	{
		print_error("shell: syntax error near unexpected token `|' or \"\n",
			2, exit_status);
		return (1);
	}
	if (ft_strcmp(result, ":") == 0)
	{
		print_error(NULL, 0, exit_status);
		return (1);
	}
	if (ft_strcmp(result, "!") == 0)
	{
		print_error(NULL, 1, exit_status);
		return (1);
	}
	if (ends_with_redirect(result) == 1)
	{
		print_error("shell: syntax error near unexpected token `<' or `>'\n",
			2, exit_status);
		return (1);
	}
	return (0);
}

typedef struct s_norminette {
	char	*result;
	char	*dollar;
	char	*spaces_removed_dollar;
	char	*replaced_env_vars;
}	t_norminette;

char	*ft_valid(char *msg, t_env **head, int *exit_status)
{
	t_norminette	norm;

	if (ft_isquotes(msg) == 0)
		return (print_error("Shell : Invalid quote\n", 130, exit_status), NULL);
	norm.result = remove_spaces(msg);
	if (valid_util(norm.result, exit_status) == 1
		|| ft_isdirec(norm.result, exit_status) == 1)
		return (free(norm.result), NULL);
	if (c_dollar(msg) == 1)
		norm.replaced_env_vars = replace_env_varss(msg, head, exit_status);
	else
		norm.replaced_env_vars = ft_strdup(msg);
	if (norm.replaced_env_vars == NULL)
		return (free(norm.result), NULL);
	norm.dollar = verify_slash(norm.replaced_env_vars);
	if (norm.dollar == NULL)
		return (free(norm.result), free(norm.replaced_env_vars), NULL);
	norm.spaces_removed_dollar = remove_spaces(norm.dollar);
	if (ft_strcmp(norm.spaces_removed_dollar, "\"\"") == 0
		|| ft_strcmp(norm.spaces_removed_dollar, "''") == 0)
		return (print_error("Shell: Command not found\n", 127, exit_status),
			free(norm.result), free(norm.dollar), free(norm.replaced_env_vars),
			free(norm.spaces_removed_dollar), NULL);
	return (free(norm.result), free(norm.spaces_removed_dollar),
		free(norm.replaced_env_vars), norm.dollar);
}

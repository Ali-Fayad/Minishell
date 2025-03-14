/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:15:49 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:38 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_variable(t_env **head, char *var, char *fullvar)
{
	t_env	*current;
	int		var_len;

	if (!head || !var || !fullvar)
		return ;
	current = *head;
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (current)
	{
		if (ft_strncmp(current->var, var, var_len) == 0)
		{
			if (current->var[var_len] == '=' || current->var[var_len] == '\0')
			{
				free(current->var);
				current->var = ft_strdup(fullvar);
				current->check = 0;
				return ;
			}
		}
		current = current->next;
	}
	ft_addvariable(head, fullvar);
}

typedef struct s_norminette2
{
	int		i;
	t_exp	*tmp;
	char	**result;
	char	*tmp_q;
	char	*tmp_q2;
}	t_norminette2;

void	export(char *msg, t_env **head, int *exit_status)
{
	t_norminette2	norm;

	norm.i = 1;
	if (export_split_helper(msg) == 1)
		return (print_export(*head));
	norm.result = export_split(msg);
	if (!norm.result)
		return ;
	while (norm.result[norm.i])
	{
		norm.tmp = parse_exp(norm.result[norm.i]);
		if (norm.tmp)
		{
			norm.tmp_q = ft_quotes(norm.tmp->var);
			norm.tmp_q2 = ft_quotes(norm.result[norm.i]);
			if (ft_isvar(norm.tmp_q, exit_status) == 1)
				update_variable(head, norm.tmp_q, norm.tmp_q2);
			free(norm.tmp_q);
			free(norm.tmp_q2);
		}
		free_exp(norm.tmp);
		norm.i++;
	}
	free_env_array(norm.result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afayad <afayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:37:27 by afayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:59:36 by afayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exp	*init_empty_exp(void)
{
	t_exp	*exp;

	exp = (t_exp *)malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	exp->var = NULL;
	exp->value = NULL;
	return (exp);
}

static	int	extract_var_name(t_exp *exp, char *msg, int var_len)
{
	char	*temp_var;

	temp_var = (char *)malloc(var_len + 1);
	if (!temp_var)
		return (0);
	v_strncpy(temp_var, msg, var_len);
	temp_var[var_len] = '\0';
	exp->var = ft_quotes(temp_var);
	free(temp_var);
	if (!exp->var)
		return (0);
	return (1);
}

static t_exp	*init_exp_struct(char *msg, char **equal_pos)
{
	t_exp	*exp;

	if (!msg || msg[0] == '\0')
		return (init_empty_exp());
	exp = (t_exp *)malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	exp->var = NULL;
	exp->value = NULL;
	*equal_pos = ft_strchr(msg, '=');
	if (!*equal_pos)
	{
		exp->var = ft_quotes(msg);
		if (!exp->var)
			return (free(exp), NULL);
	}
	return (exp);
}

static int	extract_var_value(t_exp *exp, char *equal_pos)
{
	if (*(equal_pos + 1) != '\0')
	{
		exp->value = ft_quotes(equal_pos + 1);
		if (!exp->value && exp->var)
			return (0);
	}
	return (1);
}

t_exp	*parse_exp(char *msg)
{
	t_exp	*exp;
	char	*equal_pos;
	int		var_len;

	exp = init_exp_struct(msg, &equal_pos);
	if (!exp)
		return (NULL);
	if (!equal_pos)
		return (exp);
	var_len = equal_pos - msg;
	if (var_len > 0)
	{
		if (!extract_var_name(exp, msg, var_len))
			return (free(exp), NULL);
	}
	else
	{
		exp->var = NULL;
		exp->value = NULL;
		return (exp);
	}
	if (!extract_var_value(exp, equal_pos))
		return (free(exp->var), free(exp), NULL);
	return (exp);
}

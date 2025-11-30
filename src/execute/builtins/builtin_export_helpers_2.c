/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helpers_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:16 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:17:17 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	char		*rtn;
	int			i;
	t_minishell	*shell;

	i = 0;
	shell = minishell_get();
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	rtn = fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	ft_strlcpy(rtn, str, (i + 1));
	return (rtn);
}

char	*extract_value(char *str)
{
	char		*rtn;
	int			i;
	t_minishell	*shell;

	i = 0;
	shell = minishell_get();
	while (*str && *str != '+'
		&& *str != '=')
		str++;
	if (*str && *str == '+')
		str++;
	if (*str && *str == '=')
		str++;
	i = 0;
	while (str[i])
		i++;
	rtn = fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	ft_strlcpy(rtn, str, i + 1);
	return (rtn);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:23 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:17:24 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static bool	n_flag(char *str)
{
	int	index;

	if (str == NULL || str[0] != '-')
		return (false);
	index = 1;
	while (str[index] == 'n')
		index++;
	if (str[index] == '\0' && index > 1)
		return (true);
	return (false);
}

int	builtin_echo(char **args)
{
	int		index;
	bool	newline;

	newline = true;
	index = 1;
	while (n_flag(args[index]))
	{
		index++;
		newline = false;
	}
	while (args && args[index])
	{
		ft_fprintf(STDOUT_FILENO, "%s", args[index]);
		if (args[index + 1] != NULL)
			ft_printf(" ");
		index++;
	}
	if (newline)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:18 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:20:05 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	cleanup_exit(int status)
{
	garbage_free_all();
	exit (status);
}

static void	argument_is_numeric(char *str)
{
	char	*buf;

	buf = str;
	while (*str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (!ft_isdigit(*str))
		{
			ft_fprintf(STDERR_FILENO,
				"exit: %s: numeric argument required\n", buf);
			cleanup_exit(2);
		}
		str++;
	}
}

int	builtin_exit(char **args)
{
	long long	exit_code;

	if (!args[1])
		cleanup_exit(0);
	argument_is_numeric(args[1]);
	if (args[2])
	{
		ft_fprintf(STDOUT_FILENO, "exit\n");
		ft_fprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
		if (ft_isdigit(args[1][0]))
			return (1);
		return (2);
	}
	if (!args[1][0])
	{
		ft_fprintf(STDERR_FILENO,
			"bash: exit: : numeric argument required\n");
		cleanup_exit(2);
	}
	exit_code = fti_atol_exit(args[1]);
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	cleanup_exit(exit_code);
	return (-1);
}

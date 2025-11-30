/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_atol_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:55 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:56 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_long_limit(long num, int sign, char *str, int i)
{
	int	digit;

	digit = str[i] - '0';
	if (sign == 1)
	{
		if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && digit > 7))
		{
			ft_fprintf(STDERR_FILENO,
				"bash: exit: %s: numeric argument required\n", str);
			cleanup_exit(2);
		}
	}
	else
	{
		if (num > -(LONG_MIN / 10) || (num == -(LONG_MIN / 10) && digit > 8))
		{
			ft_fprintf(STDERR_FILENO,
				"bash: exit: %s: numeric argument required\n", str);
			cleanup_exit(2);
		}
	}
}

long	fti_atol_exit(const char *str)
{
	int		i;
	long	number;
	int		multiply;

	i = 0;
	multiply = 1;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			multiply = -1;
		i++;
	}
	number = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		handle_long_limit(number, multiply, (char *)str, i);
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	number *= multiply;
	return (number);
}

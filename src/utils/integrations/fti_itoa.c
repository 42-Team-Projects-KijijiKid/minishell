/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:40 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:41 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_length(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*fti_itoa(int n)
{
	char	*array;
	int		i;
	long	num;

	num = ((long)n);
	i = get_length(n);
	array = (char *)fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	if (!array)
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		array[0] = '-';
	}
	array[i] = '\0';
	while (0 <= i && num != 0)
	{
		i--;
		array[i] = (num % 10) + '0';
		num /= 10;
	}
	if (0 == n)
		array[0] = '0';
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:03:18 by mandre            #+#    #+#             */
/*   Updated: 2025/06/09 22:45:42 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
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
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	number *= multiply;
	return (number);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char arr1[] = "2147483699999";

// 	printf("%li", ft_atol(arr1));
// }
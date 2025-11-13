/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:55:56 by mandre            #+#    #+#             */
/*   Updated: 2025/03/27 16:30:09 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_length(int n)
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

char	*ft_itoa(int n)
{
	char	*array;
	int		i;
	long	num;

	num = ((long)n);
	i = get_length(n);
	array = (char *)malloc(sizeof(char) * (i + 1));
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

// int	main(void)
// {
// 	int	test;

// 	test = -2147483648;
// 	printf("%i\n", get_length(test));
// 	printf("%s\n", ft_itoa(test));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_lowercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:32:30 by mandre            #+#    #+#             */
/*   Updated: 2025/11/20 17:54:50 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	hexa_lowercase(unsigned long val, int rtn_val)
{
	char	digit;

	rtn_val++;
	if (15 < val)
	{
		rtn_val = hexa_lowercase(val / 16, rtn_val);
		hexa_lowercase(val % 16, rtn_val);
	}
	else
	{
		if (val < 10)
			digit = '0' + val;
		else
			digit = (val - 10) + 'a';
		ft_putchar(digit);
	}
	return (rtn_val);
}

int	fhexa_lowercase(int fd, unsigned long val, int rtn_val)
{
	char	digit;

	rtn_val++;
	if (15 < val)
	{
		rtn_val = fhexa_lowercase(fd, val / 16, rtn_val);
		fhexa_lowercase(fd, val % 16, rtn_val);
	}
	else
	{
		if (val < 10)
			digit = '0' + val;
		else
			digit = (val - 10) + 'a';
		ft_fputchar(fd, digit);
	}
	return (rtn_val);
}

// int main(void)
// {
// 	unsigned int *tmp = 78200909;
//     printf("%p\n", tmp);
//     hexa_lowercase((unsigned long)tmp);
// }
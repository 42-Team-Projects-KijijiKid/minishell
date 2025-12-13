/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_uppercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:23:16 by mandre            #+#    #+#             */
/*   Updated: 2025/11/20 17:40:54 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	hexa_uppercase(unsigned long val, int rtn_val)
{
	char	digit;

	rtn_val++;
	if (15 < val)
	{
		rtn_val = hexa_uppercase(val / 16, rtn_val);
		hexa_uppercase(val % 16, rtn_val);
	}
	else
	{
		if (val < 10)
			digit = '0' + val;
		else
			digit = (val - 10) + 'A';
		ft_putchar(digit);
	}
	return (rtn_val);
}

int	fhexa_uppercase(int fd, unsigned long val, int rtn_val)
{
	char	digit;

	rtn_val++;
	if (15 < val)
	{
		rtn_val = fhexa_uppercase(fd, val / 16, rtn_val);
		fhexa_uppercase(fd, val % 16, rtn_val);
	}
	else
	{
		if (val < 10)
			digit = '0' + val;
		else
			digit = (val - 10) + 'A';
		ft_fputchar(fd, digit);
	}
	return (rtn_val);
}

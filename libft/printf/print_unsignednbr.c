/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:43:02 by mateoandre        #+#    #+#             */
/*   Updated: 2025/11/20 17:26:36 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_usigned(unsigned int val, int rtn_val)
{
	int	digit;

	if (9 < val)
	{
		rtn_val++;
		rtn_val = print_int(val / 10, rtn_val++);
		print_int(val % 10, rtn_val);
	}
	else
	{
		digit = 48 + val;
		rtn_val += ft_putchar(digit);
	}
	return (rtn_val);
}

int	fprint_usigned(int fd, unsigned int val, int rtn_val)
{
	int	digit;

	if (9 < val)
	{
		rtn_val++;
		rtn_val = fprint_int(fd, val / 10, rtn_val++);
		fprint_int(fd, val % 10, rtn_val);
	}
	else
	{
		digit = 48 + val;
		rtn_val += ft_fputchar(fd, digit);
	}
	return (rtn_val);
}

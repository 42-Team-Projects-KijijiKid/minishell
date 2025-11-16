/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:58:40 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/08 11:49:54 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_int(int val, int rtn_val)
{
	char	digit;

	if (val == -2147483648)
	{
		rtn_val = print_str("-2147483648");
		return (rtn_val);
	}
	if (val < 0)
	{
		rtn_val = ft_putchar('-');
		val *= -1;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:43:02 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/08 11:50:03 by mateoandre       ###   ########.fr       */
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

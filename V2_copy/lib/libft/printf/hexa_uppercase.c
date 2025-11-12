/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_uppercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:23:16 by mandre            #+#    #+#             */
/*   Updated: 2025/09/08 11:49:50 by mateoandre       ###   ########.fr       */
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

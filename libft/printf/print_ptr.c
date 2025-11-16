/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:18:14 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/08 11:49:57 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_ptr(unsigned long int ptr)
{
	int	rtn_val;

	rtn_val = 0;
	rtn_val = print_str("0x");
	rtn_val += hexa_lowercase(ptr, 0);
	return (rtn_val);
}

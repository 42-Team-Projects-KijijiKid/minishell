/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:18:14 by mateoandre        #+#    #+#             */
/*   Updated: 2025/11/20 17:54:44 by mandre           ###   ########.fr       */
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

int	fprint_ptr(int fd, unsigned long int ptr)
{
	int	rtn_val;

	rtn_val = 0;
	rtn_val = fprint_str(fd, "0x");
	rtn_val += fhexa_lowercase(fd, ptr, 0);
	return (rtn_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:08:42 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/08 11:50:06 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_str(char *str)
{
	int	rtn_value;

	if (!str)
		return (print_str("(null)"));
	rtn_value = -1;
	while (str[++rtn_value])
		ft_putchar(str[rtn_value]);
	return (rtn_value);
}

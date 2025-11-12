/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:15:33 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/21 17:33:47 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int arg)
{
	if (0 <= arg && arg <= 127)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     printf("%i", ft_isascii('ß'));
// }
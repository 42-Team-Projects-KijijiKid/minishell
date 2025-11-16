/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:15:12 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/16 15:21:54 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int arg)
{
	if (('a' <= arg && arg <= 'z') || ('A' <= arg && arg <= 'Z'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     printf("%i", ft_isalpha('G'));
// }
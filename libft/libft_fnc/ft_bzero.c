/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:27:39 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/16 16:15:14 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)str)[i] = (unsigned char)0;
		i++;
	}
}

// #include <stdio.h>
// int main(void)
// {
//     char buffer[] = "SeeYou";
//     printf("Before: %s\n", buffer);
//     ft_bzero(buffer, 3);
//     printf("After: %c", buffer[3]);
// }
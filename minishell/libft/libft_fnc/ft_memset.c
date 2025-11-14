/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:35:26 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/16 18:46:28 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t range)
{
	size_t	i;

	i = 0;
	while (i < range)
	{
		((unsigned char *) dst)[i] = (unsigned char)c;
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     char buffer[10];

//     ft_memset(buffer, 'b', sizeof(char) * 10);
//     // ft_memset(buffer + 5, 'g', sizeof(char) * 5);
//     // memset(buffer, 'g', sizeof(char) * 10);
//     printf("%s", buffer);
// }
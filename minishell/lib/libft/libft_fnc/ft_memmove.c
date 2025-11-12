/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:59:58 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/16 18:46:15 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (((unsigned char *) dest) < ((unsigned char *)src))
	{
		while (i < n)
		{
			((unsigned char *) dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (0 < n)
		{
			n--;
			((unsigned char *) dest)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}

// #include <unistd.h>
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     char src[] = "Hello World!";
//     ft_memmove(src + 1, src, 3);
//     printf("Output: %s", src);
// }
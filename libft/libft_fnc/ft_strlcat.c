/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:34:27 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/22 11:47:36 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		src_len;
	size_t		dst_len;
	size_t		i;
	size_t		x;

	dst_len = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0')
		dst_len++;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = 0;
	x = dst_len;
	while ((dst_len + i) < dstsize - 1 && src[i] != '\0')
	{
		dst[x] = src[i];
		i++;
		x++;
	}
	if ((dst_len + i < dstsize))
		dst[x] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     printf("Return: %lu\n", ft_strlcat("pqrstuvwxyz", "abcd", 1));
//     // printf("Output: %s", ft_strlcat("pqrstuvwxyz", "abcd", 1));
// }
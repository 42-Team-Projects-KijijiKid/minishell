/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:05 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/20 10:27:34 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	s_len;
	int		cpy_len;

	i = 0;
	s_len = 0;
	while (src[s_len] != '\0')
		s_len++;
	if (size == 0)
		return (s_len);
	if (size - 1 < s_len)
		cpy_len = size - 1;
	else
		cpy_len = s_len;
	while (i < cpy_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s_len);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     char arr1[] = "Hello World!";
//     char arr2[8];

//     // printf("Lenght: %lu\n", ft_strlen(arr2));
//     printf("Return: %lu\n", ft_strlcpy(arr2, arr1, 2));
//     printf("Output: %s", arr2);
// }
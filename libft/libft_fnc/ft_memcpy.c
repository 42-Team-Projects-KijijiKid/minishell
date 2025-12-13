/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:32:30 by mateoandre        #+#    #+#             */
/*   Updated: 2025/04/01 10:57:17 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (!dest && !src)
		return (dest);
	tmp1 = ((unsigned char *)dest);
	tmp2 = ((unsigned char *)src);
	i = 0;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i++;
	}
	return (dest);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
//     char buffer[4];
//     char tocpy[]= "15739";

//     ft_memcpy(buffer, tocpy, sizeof(char) * 4);
//     printf("%s", buffer);
// }
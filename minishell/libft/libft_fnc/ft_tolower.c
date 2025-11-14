/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:09:47 by mateoandre        #+#    #+#             */
/*   Updated: 2025/03/16 18:47:50 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (65 <= c && c <= 90)
		c += 32;
	return (c);
}

// #include <stdio.h> 
// #include <ctype.h>
// int main(void)
// {
//     int i;
//     char upper[] = "AB0EE";
//     i = 0;
//     while (upper[i] != '\0')
//     {
//         printf("Decapitalized: %c\n", (char)ft_tolower(upper[i]));
//         i++; 
//     }
// }
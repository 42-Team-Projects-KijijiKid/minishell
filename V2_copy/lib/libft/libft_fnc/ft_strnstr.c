/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:32:53 by mandre            #+#    #+#             */
/*   Updated: 2025/03/22 13:07:17 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	if (!needle && !haystack)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		x = 0;
		while (i + x < len && haystack[i + x]
			&& needle[x] && haystack[i + x] == needle[x])
			x++;
		if (needle[x] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

// #include <string.h>
// int	main(void)
// {
// 	char test1[] = "Hello this is World!";
// 	char test2[] = "this";
// 	printf("%s", ft_strnstr(test1, test2, 21));
// }
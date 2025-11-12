/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:34:07 by mandre            #+#    #+#             */
/*   Updated: 2025/03/27 10:55:11 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	val_cmp(char digit, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == digit)
			return (true);
		i++;
	}
	return (false);
}

char	*s_create(size_t begin, size_t end, const char *s1)
{
	size_t		i;
	char		*str;
	size_t		len;

	len = end - (begin - 1);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[begin + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	while (val_cmp(s1[i], set) && i < ft_strlen(s1))
		i++;
	j = ft_strlen(s1) - 1;
	while (val_cmp(s1[j], set) && i < j)
		j--;
	return (s_create(i, j, s1));
}

// int main(void)
// {
// 	char test1[] = "xxxz  test with x and z and x .  zx  xx z";
// 	printf("Before: %s\n", test1);
// 	printf("After: %s\n", ft_strtrim(test1, "z x"));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:03:26 by mandre            #+#    #+#             */
/*   Updated: 2025/11/05 09:03:27 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_find_occurence(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (true);
		i++;
	}
	return (false);
}

void	ft_memmove_gnl(char *dest, char *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return ;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	else
	{
		dest[n] = '\0';
		while (0 < n)
		{
			n--;
			dest[n] = src[n];
		}
	}
}

/// @brief Slighlty differs from the 
/// original strjoin
char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t		i;
	char		*str;

	if (!s1)
	{
		str = ft_strdup(s2);
		return (str);
	}
	if (!s2)
		return (NULL);
	str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + strlen_special(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) + strlen_special(s2))
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/// @brief Slightly different to the 
/// libft strdup 
char	*ft_strdup_gnl(const char *s)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	if (!s)
		return (NULL);
	s_len = strlen_special(s);
	ptr = (char *)malloc(sizeof(char) * s_len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		ptr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		ptr[i] = '\n';
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:40:27 by mandre            #+#    #+#             */
/*   Updated: 2025/06/15 11:23:12 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **ptr, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

const char	*get_word_index(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

int	wrd_count(char const *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

char	*write_word(char const **s, char c)
{
	int		i;
	char	*array;

	i = 0;
	while ((*s)[i] != c && (*s)[i])
		i++;
	array = (char *)malloc(sizeof(char) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	while ((*s)[i] != c && (*s)[i])
	{
		array[i] = (*s)[i];
		i++;
	}
	array[i] = '\0';
	*s += i;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = wrd_count(s, c);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		s = get_word_index(s, c);
		array[i] = write_word(&s, c);
		if (!array[i])
		{
			free_split(array, i);
			return (NULL);
		}
		i++;
	}
	array[word_count] = NULL;
	return (array);
}

// int	main(void)
// {
// 	char test[] = "";
// 	printf("After: %i\n", wrd_count(test, ' '));
// 	printf("After: %s\n", *ft_split(NULL, ' '));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:28 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:29 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static const char	*fti_get_word_index(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

static char	*fti_write_word(char const **s, char c)
{
	int		i;
	char	*array;

	i = 0;
	while ((*s)[i] != c && (*s)[i])
		i++;
	array = (char *)fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	if (!array)
		ft_error("Malloc failed", __FILE__, __LINE__, 1);
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

char	**fti_split(char const *s, char c)
{
	char	**array;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = wrd_count(s, c);
	array = (char **)fti_malloc(sizeof(char *) * (word_count + 1), TEMPORARY);
	if (!array)
		ft_error("Malloc failed", __FILE__, __LINE__, 1);
	i = 0;
	while (i < word_count)
	{
		s = fti_get_word_index(s, c);
		array[i] = fti_write_word(&s, c);
		i++;
	}
	array[word_count] = NULL;
	return (array);
}

// int	main(void)
// {
// 	char test[] = "";
// 	printf("After: %i\n", wrd_count(test, ' '));
// 	printf("After: %s\n", *fti_split(NULL, ' '));
// }
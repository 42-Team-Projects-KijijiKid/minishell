/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:13:35 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:13:37 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extend_string(char *string, int added_length)
{
	int		length;
	char	*extended_string;
	int		index;

	length = ft_strlen(string);
	extended_string = (char *)malloc(
			sizeof(char) * (length + added_length + 1));
	index = 0;
	while (index < length)
	{
		extended_string[index] = string[index];
		index++;
	}
	extended_string[length + added_length] = '\0';
	free(string);
	return (extended_string);
}

bool	reading_loop(char *character, int *buffer_size,
	int *index, char **buffer)
{
	if (*character == '\n')
		return (false);
	if (*index == *buffer_size - 1)
	{
		*buffer = extend_string(*buffer, 100);
		*buffer_size += 100;
	}
	buffer[0][*index] = *character;
	(*index)++;
	return (true);
}

char	*read_next_line(void)
{
	char	*buffer;
	char	character;
	int		buffer_size;
	int		index;

	buffer_size = 100;
	buffer = (char *)malloc(sizeof(char) * buffer_size);
	index = 0;
	while (read(STDIN_FILENO, &character, 1) > 0)
	{
		if (!reading_loop(&character, &buffer_size, &index, &buffer))
			break ;
	}
	buffer[index] = '\0';
	garbage_add_to_layer(&minishell_get()->garbage.temporary, (void *)buffer);
	return (buffer);
}

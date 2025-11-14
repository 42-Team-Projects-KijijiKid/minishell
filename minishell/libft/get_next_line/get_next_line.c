/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:03:38 by mandre            #+#    #+#             */
/*   Updated: 2025/11/05 09:03:41 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strlen_special(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	set_last_line_and_cut_static(char *left_c)
{
	size_t		i;

	i = 0;
	while (left_c[i] != '\n' && left_c[i] != '\0')
	{
		i++;
	}
	if (left_c[i] == '\n')
		i++;
	ft_memmove_gnl(left_c, left_c + i, ft_strlen(left_c + i));
}

char	*get_next_line(int fd)
{
	static char	left_c[1024][BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || 1024 < fd)
		return (NULL);
	line = NULL;
	if (*left_c[fd])
		line = ft_strdup_gnl(left_c[fd]);
	while (!ft_find_occurence(left_c[fd], '\n'))
	{
		bytes_read = read(fd, left_c[fd], BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), left_c[fd][0] = '\0', NULL);
		left_c[fd][bytes_read] = '\0';
		if (bytes_read == 0)
			return (left_c[fd][0] = '\0', line);
		tmp = line;
		line = ft_strjoin_gnl(tmp, left_c[fd]);
		if (!tmp || *tmp)
			free(tmp);
	}
	set_last_line_and_cut_static(left_c[fd]);
	return (line);
}

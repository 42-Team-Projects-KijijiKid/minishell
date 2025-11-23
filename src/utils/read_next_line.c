#include "minishell.h"

static char	*extend_string(char *string, int added_length)
{
	int		length;
	char	*extended_string;
	int		index;

	length = ft_strlen(string);
	extended_string = (char *)malloc(sizeof(char) * (length + added_length + 1));
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

char	*read_next_line(int fd)
{
	char	*buffer;
	char	character;
	int		read_bytes;
	int		buffer_size;
	int		index;

	buffer_size = 100;
	buffer = (char *)malloc(sizeof(char) * buffer_size);
	index = 0;
	while ((read_bytes = read(STDIN_FILENO, &character, 1)) > 0)
	{
		if (character == '\n')
			break;
		if (index == buffer_size -1)
		{
			buffer = extend_string(buffer, 100);
			buffer_size += 100;
		}
		buffer[index] = character;
		index++;
	}
	if (read_bytes == -1)
		ft_error("read failed", __FILE__, __LINE__, 1); // TODO: Enter Error Message
	buffer[index] = '\0';
	return (buffer);
}

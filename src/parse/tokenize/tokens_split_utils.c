#include "../../../inc/minishell.h"

static bool	is_meta(char *str)
{
	char	match;

	if (*str != '&')
		return (true);
	match = *str;
	str++;
	if (!str)
		return (false);
	if (match == *str)
		return (true);
	return (false);
}

unsigned int	count_arguments(char *str)
{
	unsigned int	words;
	char			quote;

	words = 0;
	while (*str && (!is_meta_char(*str) || !is_meta(str)))
	{
		if (*str != ' ')
			words++;
		while (*str && (!is_meta_char(*str) || !is_meta(str)) && *str != ' ')
		{
			if (*str == '\'' || *str == '\"')
			{
				quote = *str++;
				while (*str && *str != quote)
					str++;
				if (*str)
					str++;
			}
			else
				str++;
		}
		if (*str == ' ')
			str++;
	}
	return (words);
}

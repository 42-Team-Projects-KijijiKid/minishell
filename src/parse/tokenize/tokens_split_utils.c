#include "../../../inc/minishell.h"

unsigned int	count_arguments(char *str)
{
	int		words;
	char	quote;

	words = 0;
	while (*str && !is_meta_char(*str))
	{	
		while (*str && !is_meta_char(*str)
			&& *str != ' ')
		{
			if (*str == '\'' 
				|| *str == '\"')
			{
				quote = *str;
				str++;
				while (*str
					&& *str != quote)
					str++;
				str++;
			}
			else
				str++;
		}
		words++;
		if (*str == ' ')
			str++;
	}
	return (words);
}

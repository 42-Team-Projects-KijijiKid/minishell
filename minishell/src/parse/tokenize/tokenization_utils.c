#include "../../../inc/minishell.h"

/// @brief Counts the length of a single token
/// delimited by meta chars, space, or quotes
/// @param str 
/// @return length of token
int	calculate_word_length(char *str)
{
	int	i;

	i = 0;
	while (*str && !is_meta_char(*str)
			&& *str != ' '
			&& *str != '\''
			&& *str != '\"')
	{
		i++;
		str++;
	}
	return (i);
}

int	get_quoted_string_len(char *str)
{
	int		len;
	char	quote;

	quote = *str;
	str++;
	len = 1;
	while (quote != *str)
	{
		str++;
		len++;
	}
	if (*str ==  quote)
		len++;
	return (len);
}

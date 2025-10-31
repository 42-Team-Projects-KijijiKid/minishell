#include "parsing.h"

/// @brief Checks if the quote pair has
/// content so its not '' or "".
/// And skips the conetent till pairing quote
/// @param str 
/// @return false if there is no quote content
/// true if there is quote content
bool	quote_content(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	if (quote == **str)
		return (false);
	while (**str != quote && **str)
		(*str)++;
	return (true);
}

/// @brief Count words till operator
/// or end of str handling quotes.
/// @param str 
/// @return amount of words till operator
/// or null termination
int	word_count(char *str)
{
	int		words;
	bool	flag;

	words = 0;
	flag = true;
	while (*str)
	{	
		if (flag && *str == '\'' || *str == '\"')
		{
			if (quote_content(&str))
				words++;
		}
		else if (flag && *str != ' '
			&& !is_meta_char(*str))
		{
			flag = false;
			words++;
		}
		else if (*str == ' ')
			flag = true;
		str++;
	}
	return (words);
}

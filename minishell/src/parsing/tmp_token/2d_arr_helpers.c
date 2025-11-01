#include "parsing.h"

/// @brief If Quote has content so its
/// not just '' or "" than it skips content
/// @param str 
void	quote_content(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	if (quote == **str)
		return ;
	while (**str != quote && **str)
		(*str)++;
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
	while (*str && !is_meta_char(*str))
	{	
		if (flag && *str == '\'' || *str == '\"')
		{
			quote_content(&str);
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

#include "parsing.h"

int	len_in_quotes(char *str)
{
	int		len;
	char	quote;

	quote = *str;
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

/// @brief This function creates the string in
/// quotes including the outher quotes.
/// To determine
/// @param str 
/// @return 
char	*str_in_quotes(char **str)
{
	char	quote;
	char	*rtn;
	int		len;
	int		i;

	len = len_in_quotes(*str);
	rtn = ft_malloc((sizeof(char) * len) + 1, LAYER_2);
	quote = **str;
	rtn[0] = **str;
	(*str)++;
	i = 1;
	while (quote != **str)
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i++] = **str;
	(*str)++;
	rtn[i] = '\0';
	return (rtn);
}

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
		if ((*str == '\'' || *str == '\"'))
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

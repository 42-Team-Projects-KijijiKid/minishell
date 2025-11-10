#include "../../../inc/minishell.h"

/// @brief Extracts a quoted string including the outer quotes.
/// Handles both single and double quotes properly.
/// @param str Pointer to string starting with quote character
/// @return Allocated string containing the complete quoted token
char	*extract_quoted_string(char **str)
{
	char	quote;
	char	*rtn;
	int		len;
	int		i;

	len = get_quoted_string_len(*str);
	rtn = ft_malloc((sizeof(char) * len) + 1, TEMPORARY);
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

char	*extract_unquoted_string(char **str)
{
	int		i;
	int		len;
	char	*rtn;

	len = calculate_word_length(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), TEMPORARY);
	i = 0;
	while (**str && !is_meta_char(**str)
			&& **str != ' ' && **str != '\''
			&& **str != '\"')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*extract_next_token(char **str)
{
	char	*rtn;

	while (**str)
	{
		while (**str && **str == ' ')
			(*str)++;
		if (**str == '\'' || **str == '\"')
			return (extract_quoted_string(str));
		else
			return (extract_unquoted_string(str));
	}
	return (rtn);
}

/// @brief Tokenizes a command string into a 2D array
/// Processes tokens until end of command or operator is reached.
/// Handles quote rules and removes empty quotes.
/// Does not handle variable expansion!
/// @param str Command string pointer
/// @return Array of tokens with bash quote rules applied
/// until end of command or operator is reached
char	**tokenize_command(char **str)
{
	int		i;
	char	**rtn;
	int		words;

	words = word_count(*str);
	printf("Words: %d\n", words);
	rtn = ft_malloc(sizeof(char *) * (words + 1), TEMPORARY);
	i = 0;
	while (i < words)
	{
		rtn[i] = extract_next_token(str);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

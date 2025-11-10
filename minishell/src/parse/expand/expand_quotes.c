#include "../../../inc/minishell.h"

/// @brief Counts the length of content inside quotes
/// @param content String pointer positioned after opening quote
/// @param closing_quote The quote character to match (' or ")
/// @return Length of content before closing quote
int	calculate_quoted_content_length(char *content, char closing_quote)
{
	int	length;

	length = -1;
	while (*content != closing_quote && content)
	{
		content++;
		length++;
	}
	return (length);
}

/// @brief Extracts content from single quotes without expansion
/// Removes outer single quotes but preserves inner content
/// @param quoted_str String starting with single quote
/// @return Extracted string without outer quotes
char	*extract_single_quoted_content(char *quoted_str)
{
	int		content_length;
	char	*result;
	int		i;

	if (*quoted_str == '\'')
		quoted_str++;
	content_length = calculate_quoted_content_length(quoted_str, '\'');
	result = fti_malloc(sizeof(char) * content_length + 1, TEMPORARY);
	i = 0;
	while (*quoted_str != '\'')
	{
		result[i] = *quoted_str;
		quoted_str++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

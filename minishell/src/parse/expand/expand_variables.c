#include "minishell.h"

/// @brief Extracts a variable name from string until delimiter
/// Stops at space, metachar, or dollar sign
/// @param str_ptr Pointer to string pointer for advancement
/// @return Isolated variable name string
static char	*extract_variable_name(char **str_ptr)
{
	int		name_length;
	char	*variable_name;

	name_length = 0;
	while ((*str_ptr)[name_length] && (*str_ptr)[name_length] != ' ' && \
		!is_meta_char((*str_ptr)[name_length]) && (*str_ptr)[name_length] != '$')
		name_length++;
	variable_name = fti_malloc((sizeof(char) * name_length) + 1, TEMPORARY);
	name_length = 0;
	while (**str_ptr && **str_ptr != ' ' && !is_meta_char(**str_ptr) && \
		**str_ptr != '$')
	{
		variable_name[name_length] = **str_ptr;
		(*str_ptr)++;
		name_length++;
	}
	variable_name[name_length] = '\0';
	return (variable_name);
}

/// @brief Calculates total length needed for string with expansions
/// @param content String content to process
/// @param closing_quote Quote character marking end
/// @return Total length including expanded variable values
static unsigned int	calculate_expanded_length(char *content, char closing_quote)
{
	int		literal_length;
	int		expanded_length;
	char	*variable_name;

	literal_length = 0;
	expanded_length = 0;
	while (*content != closing_quote && *content)
	{
		if (*content == '$')
		{
			content++;
			variable_name = extract_variable_name(&content);
			// expanded_length += ft_strlen(get_env_value(variable_name));
		}
		if (*content && *content != closing_quote)
			literal_length++;
		if (*content != '$')
			content++;
	}
	return (literal_length + expanded_length);
}

/// @brief Retrieves environment variable value for expansion
/// @param str_ptr Pointer to string pointer starting at/after $
/// @return Value of environment variable or NULL
static char	*get_expanded_variable_value(char **str_ptr)
{
	char	*variable_name;
	char	*variable_value;

	if (**str_ptr == '$')
		(*str_ptr)++;
	else
		return (NULL);
	variable_name = extract_variable_name(str_ptr);
	// variable_value = get_env_value(variable_name);
	return (variable_value);
}

/// @brief Expands variables inside quoted string
/// Replaces $VAR with actual values
/// @param content String content after opening quote
/// @param closing_quote Quote character to stop at
/// @return New string with expansions applied
char	*expand_variables_in_quotes(char *content, char closing_quote)
{
	char	*result;
	char	*variable_value;
	int		index;

	result = fti_malloc((sizeof(char) * calculate_expanded_length(content, \
		closing_quote)) + 1, TEMPORARY);
	index = 0;
	while (*content != closing_quote && *content)
	{
		if (*content == '$')
		{
			variable_value = get_expanded_variable_value(&content);
			while (*variable_value)
			{
				result[index++] = *variable_value;
				variable_value++;
			}
		}
		if (*content != closing_quote && *content && *content != '$')
			result[index++] = *content;
		if (*content != '$')
			content++;
	}
	result[index] = '\0';
	return (result);
}

/// @brief Handles double quoted strings with variable expansion
/// @param quoted_str String starting with double quote
/// @return Expanded string without outer quotes
char	*extract_double_quoted_with_expansion(char *quoted_str)
{
	if (*quoted_str == '\"')
		quoted_str++;
	else
		ft_error("Invalid string for double quote expansion", \
			__FILE__, __LINE__, 73);
	return (expand_variables_in_quotes(quoted_str, '\"'));
}

/// @brief Expands a standalone variable (not in quotes)
/// @param variable_str String starting with $
/// @return Expanded variable value
char	*expand_standalone_variable(char *variable_str)
{
	char	*result;
	char	*variable_value;

	if (*variable_str == '$')
		variable_str++;
	else
		ft_error("Invalid string for variable expansion", \
			__FILE__, __LINE__, 73);
	// variable_value = get_env_value(variable_str);
	if (!variable_value)
		return (NULL);
	result = ft_strdup(variable_value);
	return (result);
}

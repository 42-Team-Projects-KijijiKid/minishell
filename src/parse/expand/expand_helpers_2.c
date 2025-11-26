#include "minishell.h"

bool	quote_has_content(char *str)
{
	char	quote;

	if (*str != '\''
		|| *str != '\"')
		return (true);
	quote = *str;
	str++;
	if (quote == *str)
		return (false);
	while (*str != quote && *str)
		str++;
	return (true);
}

/// @brief Null ends a possible expansion
/// string isolate from rest of the string
/// @param str str thats in quotes
/// @return isolated string
char	*null_end_str(char **str)
{
	int		i;
	char	*rtn;

	rtn = *str;
	i = 0;
	while ((*str)[i] && (*str)[i] != ' ' && !is_meta_char((*str)[i])
			&& (*str)[i] != '$' && (*str)[i] != '\"'
			&& (*str)[i] != '\'' && (*str)[i] != '/')
		i++;
	rtn = fti_malloc((sizeof(char) * i) + 1, TEMPORARY);
	i = 0;
	while (**str && **str != ' ' && !is_meta_char(**str)
		&& **str != '$' && **str != '\"'
		&& **str != '\'' && **str != '/')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

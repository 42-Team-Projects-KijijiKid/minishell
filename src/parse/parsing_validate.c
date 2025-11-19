#include "../../inc/minishell.h"

static bool	find_matching_quote(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (**str && **str == quote)
	{
		(*str)++;
		return (true);
	}
	return (false);
}

/// @brief This checking for syntax errors.
/// Uneven amount of quotes. But impotant are also
/// cases like "'" because this is a valid expression
/// the check_withing functions handle thesee cases.
/// @param line 
int	validate_quote_pairs(char *line)
{
	unsigned int	double_quote;
	unsigned int	single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			if (!find_matching_quote(&line))
				return (error_msg("Syntax Error", __FILE__, __LINE__, 2));
		}
		else if (*line == '\"')
		{
			if (!find_matching_quote(&line))
				return (error_msg("Syntax Error", __FILE__, __LINE__, 2));
		}
		if (*line
			&& *line != '\''
			&& *line != '\"')
			line++;
	}
	return (0);
}

#include "parsing.h"

bool	check_within(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str != quote && **str)
		(*str)++;
	if (**str == quote)
		return (true);
	return (false);
}

/// @brief This checking for syntax errors.
/// Uneven amount of quotes. But impotant are also
/// cases like "'" because this is a valid expression
/// the check_withing functions handle thesee cases.
/// @param line 
void	check_quotes(char *line)
{
	unsigned int	double_quote;
	unsigned int	single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			if (check_within(&line))
				single_quote++;
			single_quote++;
		}
		if (*line == '\"')
		{
			if (check_within(&line))
				double_quote++;
			double_quote++;
		}
		line++;
	}
	if (double_quote % 2)
		ft_error("Syntax Error:", __FILE__, __LINE__, 5);
	if (single_quote % 2)
		ft_error("Syntax Error:", __FILE__, __LINE__, 5);
}

/// @brief This function goes strough the
/// provided command string checking for syntax
/// errors
/// @param line 
void	check_syntax(char *line)
{
	check_quotes(line);
}

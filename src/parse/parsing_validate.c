#include "../../inc/minishell.h"

static bool	find_matching_quote(char **str)
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
void	validate_quote_pairs(char *line)
{
	unsigned int	double_quote;
	unsigned int	single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			if (find_matching_quote(&line))
				single_quote++;
			single_quote++;
		}
		if (*line == '\"')
		{
			if (find_matching_quote(&line))
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

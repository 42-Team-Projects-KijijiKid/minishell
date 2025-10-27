#include "parsing.h"

void	check_quotes(char *line)
{
	unsigned int	double_quote;
	unsigned int	single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			single_quote++;
		if (*line == '\"')
			double_quote++;
		line++;
	}
	if (double_quote % 2)
	{
		ft_error("Syntax Error:", __FILE__, __LINE__, 5);
	}
	if (single_quote % 2)
	{
		ft_error("Syntax Error:", __FILE__, __LINE__, 5);
	}
}

void	checlk_syntac(char *line)
{
	check_quotes(line);
}

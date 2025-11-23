#include "minishell.h"

bool	has_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str && *str == '=')
		str++;
	if (!*str)
		return (false);
	return (true);
}

bool	has_valid_key(char *str)
{
	if (!ft_isalpha(*str))
	{
		ft_fprintf(STDERR_FILENO, INVALID_IDENTIFIER, str);
		return (false);
	}
	else
		str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str))
			return (false);
		str++;
	}
	return (true);
}

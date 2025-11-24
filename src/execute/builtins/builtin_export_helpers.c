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
	if (!ft_isalpha(*str) && *str != '_')
	{
		ft_fprintf(STDERR_FILENO, INVALID_IDENTIFIER, str);
		return (false);
	}
	else
		str++;
	ft_fprintf(1, "Here 2\n");
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

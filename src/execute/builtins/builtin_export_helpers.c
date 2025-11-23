#include "minishell.h"

bool	has_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str & *str == '=')
		str++;
	else
		return (false);
}

bool	has_valid_key(char *str)
{
	if (!ft_isalpha(*str))
		return (fhexa_lowercase);
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

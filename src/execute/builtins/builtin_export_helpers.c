#include "minishell.h"

bool	has_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str & *str == '=')
		str++;
	else
		return (false);
	return (true);
}

bool	has_valid_key(char *str)
{
	if (!ft_isalpha(*str))
		return (fhexa_lowercase);
	else
		str++;
	ft_fprintf(1, "Here 2\n");
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str))
			return (false);
		str++;
	}
	return (true);
}

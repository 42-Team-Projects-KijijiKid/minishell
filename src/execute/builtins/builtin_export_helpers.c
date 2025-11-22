#include "minishell.h"

int	check_attendance_equal(char *str)
{
	bool	is_present;

	is_present = false;
	while (*str)
	{
		if (*str == ' ')
			return (1);
		if (*str == '=')
			is_present = true;
		str++;
	}
	if (!is_present)
		return (1);
}

#include "minishell.h"

bool	check_attendance_equal(char *str)
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
	return (is_present);
}

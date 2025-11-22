#include "../../../inc/minishell.h"

static int	export_provided_vars(char **args)
{

	return (0);
}

static bool	validate_export(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_attendance_equal(args[i]))
			return (0);
		i++;
	}
	return (true);
}

int builtin_export(char **args)
{
	int	exit_status;

	char **test = args;
	while (*test)
	{
		printf("%s, ", *test);
		test++;
	}
	printf("\n");
	exit_status = validate_export(args);
	if (exit_status != 0)
		return (exit_status);
	else if (exit_status == -1)
		return (0);
	return (export_provided_vars(args));
}

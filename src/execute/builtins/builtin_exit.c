#include "../../../inc/minishell.h"

int builtin_exit(char **args)
{
	int status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	exit (status);
}

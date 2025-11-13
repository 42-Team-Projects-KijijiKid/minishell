#include "../../../inc/minishell.h"

void builtin_exit(char **args)
{
	int status = 0;
	if (args[1])
		status = ft_atoi(args[1]); // TODO: New version required, that adds to garbage collector
	exit(status);
}

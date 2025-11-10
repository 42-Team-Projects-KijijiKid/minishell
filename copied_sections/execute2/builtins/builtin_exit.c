#include "../../../inc/minishell.h"

int builtin_exit(char **args)
{
	int status = 0;
	if (!args)
		return (ft_error("exit: invalid arguments", __FILE__, __LINE__, 1), 1);
	if (args[1])
		status = ft_atoi(args[1]); // New version required, that adds to garbage collector
	exit(status);
	return (0);
}

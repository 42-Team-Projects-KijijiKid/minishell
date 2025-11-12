#include "../../../inc/minishell.h"

void builtin_unset(char **args)
{
	int i;

	if (!args)
		return (1);
	i = 1;
	while (args[i])
	{
		env_unset_value(args[i]);
		i++;
	}
	exit(0);
}

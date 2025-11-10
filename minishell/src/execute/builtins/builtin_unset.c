#include "../../../inc/minishell.h"

int builtin_unset(char **args)
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
	return (0);
}

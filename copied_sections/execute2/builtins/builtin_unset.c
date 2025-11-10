#include "../../../inc/minishell.h"

int builtin_unset(char **args)
{
	int i;

	if (!args)
		return (1);
	i = 1;
	while (args[i])
	{
		unset_env_var(args[i]);
		i++;
	}
	return (0);
}

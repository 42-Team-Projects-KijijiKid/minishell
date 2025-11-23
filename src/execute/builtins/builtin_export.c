#include "../../../inc/minishell.h"

int builtin_export(char **args)
{
	int	i;
	int	exit;
	i = 0;
	if (!args[1])
	{
		print_sorted_exported();
		return (0);
	}
	while (args[i])
	{
		exit = export_variable(args[i]);
		i++;
	}
	return (exit);
}

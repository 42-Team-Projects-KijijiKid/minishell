#include "../../../inc/minishell.h"

static int	export_variable(char *str)
{
	if (has_valid_key(str))
		return (1);
	if (has_value(str))
		export_key_value_variable(str);
	else
		export_key_only(str);
	return (0);
}

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
		if (exit == 1)
			break ;
		i++;
	}
	return (exit);
}

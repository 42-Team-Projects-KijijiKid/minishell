#include "../../../inc/minishell.h"

static bool	check_for_concat(char *str)
{
	while (*str && *str != '=')
	{
		if (*str == '+')
			return (true);
		str++;
	}
	return (false);
}

static void	export_key_value_variable(char *str)
{
	if (check_for_concat(str))
		concatenate_env(str);
	else
		export_to_env(str);
	return ;
}

static void	export_key_only(char *str)
{
	char	*buf;

	buf = str;
	while (*buf && *buf != '=')
		buf++;
	if (*buf == '=')
		*buf = '\0';
	env_set_value(str, NULL);
}

static int	export_variable(char *str)
{
	if (!has_valid_key(str))
		return (1);
	if (has_value(str))
		export_key_value_variable(str);
	else
		export_key_only(str);
	return (0);
}

int	builtin_export(char **args)
{
	int	i;
	int	exit;

	if (!args[1])
	{
		print_sorted_exported();
		return (0);
	}
	i = 1;
	while (args[i])
	{
		exit = export_variable(args[i]);
		if (exit == 1)
			break ;
		i++;
	}
	return (exit);
}

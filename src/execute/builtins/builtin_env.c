#include "../../../inc/minishell.h"

static bool	check_if_has_value(char *str)
{
	while (*str)
	{
		if (*str == '=')
		{
			str++;
			if (*str)
				return (true);
		}
		str++;
	}
	return (false);
}

// TODO: implement builtin_env
// Functions exist in different branch:
// env_to_2d_array
// print_2d_array
int	builtin_env(char **args)
{
	char	**env;

	if (args[1])
	{
		print_error(NO_FILE_DIR, 127);
		return (127);
	}
	env = env_list_to_2d();
	if (!env)
	{
		ft_fprintf(2, ENV_LIST_EMPTY);
		return (1);
	}
	while (env && *env)
	{
		if (check_if_has_value(*env))
			ft_fprintf(STDOUT_FILENO, "%s\n", *env);
		env++;
	}
	return (0);
}

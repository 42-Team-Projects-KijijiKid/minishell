#include "../../../inc/minishell.h"

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
	while (env && *env)
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", *env);
		env++;
	}
	return (0);
}

#include "../../../inc/minishell.h"

int	builtin_env(void)
{
	// TODO: implement builtin_env
	// Functions exist in different branch:
	// env_to_2d_array
	// print_2d_array
	char	**env;

	env =  env_list_to_2d();
	while (env && *env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}

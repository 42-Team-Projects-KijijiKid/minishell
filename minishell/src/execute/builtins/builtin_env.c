#include "../../../inc/minishell.h"

/// @brief This function turns the
/// env linked list in 2D array for
/// execeve
/// @param  
/// @return 2D array of env variables 
static char	**env_list_to_2d(void) // turn_2d() in expansion/create_inv.c
{
	t_minishell	*shell;
	t_env_node	*node;
	char		**rtn;
	int			i;
	
	shell = minishell_get();
	rtn = fti_malloc(sizeof(char *) * (shell->env.size + 1), PERSISTENT);
	node = shell->env.tail;
	i = 0;
	while (node)
	{
		rtn[i] = rtn_key_value(node);
		node = node->prev;
		i++; 
	}
	rtn[i] = NULL;
	return (rtn);
}

void	builtin_env(char **args)
{
	// TODO: implement builtin_env
	// Functions exist in different branch:
	// env_to_2d_array
	// print_2d_array
	char	**env;

	env =  env_list_to_2d();
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	exit(0);
}

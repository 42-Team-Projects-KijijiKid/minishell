#include "../../inc/minishell.h"

int execute_subshell(t_tree_node *node)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
	{
		execute_node_by_type(node);
		ft_error("Nodes never exited subshell process", __FILE__, __LINE__, 990);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			ft_error("Unexpected error in subshell execution", __FILE__, __LINE__, 991);
	}
	exit(0);
}

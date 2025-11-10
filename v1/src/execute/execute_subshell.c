#include "../../inc/minishell.h"

int execute_subshell(t_tree_node *node)
{
	int	pid;
	int	status;

	if (!node || node->sub != true)
		return (ft_error("Invalid node for subshell execution", __FILE__, __LINE__, 100), 100);
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	if (pid == 0)
	{
		status = execute_node_by_type(node);
		_exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (ft_error("Unexpected error in subshell execution", __FILE__, __LINE__, 1), 0);
	}
}

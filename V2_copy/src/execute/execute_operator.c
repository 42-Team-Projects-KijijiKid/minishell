#include "../../inc/minishell.h"

void	execute_and(t_tree_node *node)
{
	int	pid;
	int	pid_child;
	int	status;

	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
		execute_node(node->left);
	else
	{
		waitpid(pid, &status, 0);
		if (!status) // TODO: Question: Exit status, when successfull 0 or >0? -> adapt here and in or function
			execute_node(node->right);
	}
}

void	execute_or(t_tree_node *node)
{
	int	pid;
	int	pid_child;
	int	status;

	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
		execute_node(node->left);
	else
	{
		waitpid(pid, &status, 0);
		if (status) // TODO: Question: Exit status, when successfull 0 or >0? -> adapt here and in and function
			execute_node(node->right);
	}
}

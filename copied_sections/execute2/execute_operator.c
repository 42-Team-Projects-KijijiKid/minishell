#include "../../inc/minishell.h"

typedef enum e_operator
{
	OP_AND,
	OP_OR
}	e_operator;


// TODO: Error handling is needs to be correctly implemented.
// Exit statuses need to be properly propagated.

static void	execute_right_node(t_token *node, int status_left, e_operator operator)
{
	int	pid_child;
	int	status;

	if ((operator == OP_AND && status_left == 0) || (operator == OP_OR && status_left != 0))
	{
		pid_child = fork();
		if (pid_child == -1)
		{
			ft_error("Fork failed", __FILE__, __LINE__, 92);
			_exit(1);
		}
		if (pid_child == 0)
		{
			status = execute_node(node->right);
			_exit(status);
		}
		else
		{
			waitpid(pid_child, &status, 0);
			_exit(WEXITSTATUS(status));
		}
	}
	else
		_exit(status_left);
}

int	execute_and(t_token *node)
{
	int	pid;
	int	pid_child;
	int	status;

	if (!node || node->type != AND_IF)
		return (ft_error("Invalid node for AND execution", __FILE__, __LINE__, 95), 95);
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	if (pid == 0)
	{
		status = execute_node(node->left);
		execute_right_node(node, status, OP_AND);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status)); // Was gibt das zurueck? Besser mit ft_error kombinieren.
}

int	execute_or(t_token *node)
{
	int	pid;
	int	pid_child;
	int	status;

	if (!node || node->type != OR_IF)
		return (ft_error("Invalid node for OR execution", __FILE__, __LINE__, 9), 97);
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	if (pid == 0)
	{
		status = execute_node(node->left);
		execute_right_node(node, status, OP_OR);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

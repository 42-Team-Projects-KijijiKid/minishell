#include "../../inc/minishell.h"

void	execute_node_by_type(t_tree_node *node)
{
	if (node->type == AND_IF)
		return (execute_and(node));
	else if (node->type == OR_IF)
		return (execute_or(node));
	else if (node->type == PIPE)
		return (execute_pipe(node));
	else if (node->type == TEXT)
		return (execute_command(node));
	ft_error("Unknown AST node type", __FILE__, __LINE__, 94);
}

void	execute_node(t_tree_node *node)
{
	if (node == NULL)
		ft_error("NULL AST node", __FILE__, __LINE__, 93);
	if (node->sub)
		execute_subshell(node);
	execute_node_by_type(node);
}

void minishell_execute()
{
	t_minishell	*shell;
	int			pid;
	int			wstatus;

	shell = minishell_get();
	if (shell->tree_root == NULL)
		ft_error("No AST to execute", __FILE__, __LINE__, 91);
	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
		execute_node(shell->tree_root);
	else
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			shell->last_exit_status = WEXITSTATUS(wstatus); // TODO: Update minishell with last exit status?
		else
			shell->last_exit_status = 1;
	}
}

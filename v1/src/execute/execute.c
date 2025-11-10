#include "../../inc/minishell.h"

int	execute_node_by_type(t_tree_node *node)
{
	if (node->type == AND_IF)
		return (execute_and(node));
	else if (node->type == OR_IF)
		return (execute_or(node));
	else if (node->type == PIPE)
		return (execute_pipe(node));
	else if (node->type == LESS)
		return (execute_rdr_in(node));
	else if (node->type == GREAT)
		return (execute_rdr_out(node));
	else if (node->type == DGREAT)
		return (execute_rdr_append(node));
	else if (node->type == DLESS)
		return (execute_rdr_heredoc(node));
	else if (node->type == TEXT)
		return (execute_command(node));
	return (ft_error("Unknown AST node type", __FILE__, __LINE__, 94), 94);
}

int	execute_node(t_tree_node *node)
{
	if (node == NULL)
		return (ft_error("Null AST node", __FILE__, __LINE__, 93), 93);
	if (node->sub)
		return (execute_subshell(node));
	return (execute_node_by_type(node));
}

void minishell_execute()
{
	t_minishell	*shell;
	int			pid;

	shell = minishell_get();
	if (shell->tree_root == NULL)
		return (ft_error("No AST to execute", __FILE__, __LINE__, 91));
	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92));
	if (pid == 0)
	{
		int exit_status = execute_node(shell->tree_root);
	}
	else
	{
		int wstatus;
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			shell->last_exit_status = WEXITSTATUS(wstatus); // Update minishell with last exit status
		else
			shell->last_exit_status = 1;
	}
}

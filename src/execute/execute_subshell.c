#include "../../inc/minishell.h"

void	execute_subshell(t_tree_node *node)
{
	int			pid;
	t_minishell	*shell;
	int			status;

	pid = ft_fork();
	shell = minishell_get();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
	{
		execute_node_by_type(node);
		garbage_free_all();
		exit(shell->last_exit_status);
	}
	if (waitpid(pid, &status, 0) == -1)
		shell->last_exit_status = 127;
	else if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
	sig_init();
}

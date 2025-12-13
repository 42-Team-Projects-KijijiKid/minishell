#include "minishell.h"

void	add_fd_to_list(int fd)
{
	t_minishell	*shell;
	t_fd_node	*new_node;

	shell = minishell_get();
	new_node = fti_malloc(sizeof(t_fd_node), TEMPORARY);
	new_node->fd = fd;
	new_node->next = shell->fd_table.head;
	shell->fd_table.head = new_node;
	shell->fd_table.size++;
}

void	default_filedescripor(void)
{
	t_minishell	*shell;

	shell = minishell_get();
	dup2(shell->filedescriptor.std_in, STDIN_FILENO);
	dup2(shell->filedescriptor.std_out, STDOUT_FILENO);
	dup2(shell->filedescriptor.std_err, STDERR_FILENO);
}

void	close_default_filedescriptor(void)
{
	t_minishell	*shell;

	shell = minishell_get();
	close(shell->filedescriptor.std_in);
	close(shell->filedescriptor.std_out);
	close(shell->filedescriptor.std_err);
}

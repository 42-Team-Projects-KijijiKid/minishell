#include "minishell.h"

// void	add_fd_to_list(int fd, )
// {

// }

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

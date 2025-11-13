#include "../../../inc/minishell.h"

void execute_rdr_out(t_redirect_node *redirect)
{
	int	fd;
	char *filename;
	int	saved_stdout;

	filename = redirect->file;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Failed to open file for output redirection", __FILE__, __LINE__, 951);
	saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		ft_error("Failed to duplicate file descriptor for output redirection", 
			__FILE__, __LINE__, 952);
	}
	close(fd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

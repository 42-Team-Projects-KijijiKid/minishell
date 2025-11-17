#include "../../../inc/minishell.h"

void execute_rdr_append(t_redirect_node *redirect)
{
	int	fd;
	int	saved_stdout;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		ft_error("Failed to open file for append redirection", __FILE__, __LINE__, 951);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		ft_error("Failed to duplicate file descriptor for append redirection", \
			__FILE__, __LINE__, 952);
	}
	close(fd);
}

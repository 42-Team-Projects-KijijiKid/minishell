#include "../../../inc/minishell.h"

void execute_rdr_in(t_redirect_node *redirect)
{
	int	fd;

	fd = open(redirect->file, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file for input redirection", __FILE__, __LINE__, 951);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		ft_error("Failed to duplicate file descriptor for input redirection", 
			__FILE__, __LINE__, 12);
	}
	close(fd);
}

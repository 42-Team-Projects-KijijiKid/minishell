#include "../../../inc/minishell.h"

int execute_rdr_in(t_redirect_node *redirect)
{
	int	fd;

	fd = open(redirect->file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: No such file or directory\n", redirect->file);
		return (1);
	}
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		ft_error("Failed to duplicate file descriptor for input redirection", 
			__FILE__, __LINE__, 12);
	}
	close(fd);
}

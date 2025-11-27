#include "../../../inc/minishell.h"

int	execute_rdr_append(t_redirect_node *redirect)
{
	int	fd;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		ft_fprintf(2, INFILE_NOT_FOUND, redirect->file);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		ft_error(DUP2_FAILED, __FILE__, __LINE__, 131);
	}
	close(fd);
	return (0);
}

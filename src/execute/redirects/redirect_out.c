#include "../../../inc/minishell.h"

int	execute_rdr_out(t_redirect_node *redirect)
{
	int		fd;
	char	*filename;

	filename = redirect->file;
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, OUTFILE_PERMISSION_DENIED, filename);
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

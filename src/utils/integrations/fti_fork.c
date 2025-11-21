#include "minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (0 < pid)
	{
		close_default_filedescripor();
		sig_reset();
	}
	return (pid);
}
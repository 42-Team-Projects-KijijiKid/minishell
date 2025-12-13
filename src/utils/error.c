#include "minishell.h"

static void	clean_exit(u_int64_t status)
{
	garbage_free_all();
	exit(status);
}

void	ft_error(char *msg, char *file, int line, u_int64_t status)
{
	ft_fprintf(2, "%s: In file \033[34m%s\033[0m \
		on \033[31mline %d\033[0m\n", msg, file, line);
	clean_exit(status);
}

int	print_error(char *msg, unsigned char status)
{
	t_minishell	*shell;

	shell = minishell_get();
	ft_fprintf(2, "%s\n", msg);
	shell->last_exit_status = status;
	return (status);
}

#include "minishell.h"

static void	clean_exit(u_int64_t exit_stat)
{
	t_minishell	*meta;

	meta = minishell_get();
	garbage_free_all();
	exit(exit_stat);
}

void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat)
{
	fprintf(stderr, "%s: In file \033[34m%s\033[0m on \033[31mline %d\033[0m\n", msg, file, line);
	clean_exit(exit_stat);
}

#include "minishell.h"

static void	clean_exit()
{
	t_meta	*meta;

	meta = get_meta();

}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	fprintf(STDERR_FILENO, "%s: In file %s on line %d\n", msg, file, line);
	clean_exit();
}

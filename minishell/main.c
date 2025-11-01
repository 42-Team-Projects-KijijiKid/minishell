#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	// echo ''''"Hello '$USER'"''''
	meta = init_meta(envp);
	while (1)
	{
		cmd = ft_readline("\033[34mMinishell>> ");
		if (!cmd)
			break ;
		parsing_process(cmd);
		execution_process(meta->head);
		free_layer(&meta->garbage.layer_2);
		free_layer(&meta->garbage.layer_3);
	}
	printf("\033[37;5mGoodbye!\033[0m\n");
	free_gc();
}

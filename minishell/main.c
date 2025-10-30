#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	meta = init_meta(envp);
	while (1)
	{
		// cmd = readline("\033[34mMinishell>>\033[34m ");
		cmd = "ls -l > out.txt";
		parsing_process(cmd);
		exit (100);
		execution_process(meta->head);
		free_layer(&meta->garbage.layer_2);
		free_layer(&meta->garbage.layer_3);
		break;
	}
	// printf("Command Print: %s\n", cmd);
	// parsing_process(cmd);
	// execution_process(meta->head);
	// free_gc();
}

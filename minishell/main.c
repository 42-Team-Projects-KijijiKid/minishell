#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	meta = init_meta(envp);
	// while (1)
	// {
	// 	cmd = readline("Minishell>> ");
	// 	printf("Command Print: %s\n", cmd);
	// 	parsing_process(cmd);
	// 	free_gc();
	// }
	// cmd = "ps -ef | grep systemd | awk '{print $2}' | grep -v grep";
	// cmd = "echo \"$PATH$USER\"";
	cmd = "echo \"$USER\"";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd);
	char *a = *meta->head->args_2d;
	char *b = meta->head->args_2d[1];

	execution_process(meta->head); 
	free_gc();
}

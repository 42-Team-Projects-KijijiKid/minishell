#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	meta = init_meta(env);
	// while (1)
	// {
	// 	cmd = readline("Minishell>> ");
	// 	printf("Command Print: %s\n", cmd);
	// 	parsing_process(cmd);
	// }
	// cmd = "ps -ef | grep systemd | awk '{print $2}' | grep -v grep";
	cmd = "echo \"\'Hello World Chiau\'\" && ls -l";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd);
	// execution_process(meta->head); 
	free_gc();
}

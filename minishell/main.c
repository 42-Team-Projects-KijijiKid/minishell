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
	// }
	// cmd = "ps -ef | grep systemd | awk '{print $2}' | grep -v grep";
	cmd = "USER";
	printf("Command Print: %s\n", cmd);
	printf("%s\n", rtn_env_value(cmd));
	parsing_process(cmd);
	// execution_process(meta->head); 
	free_gc();
}

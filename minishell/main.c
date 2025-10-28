#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	meta = init_meta(envp);
	while (1)
	{
		cmd = readline("Minishell>> ");
		printf("Command Print: %s\n", cmd);
		parsing_process(cmd);
		execution_process(meta->head);
		free_gc();
	}
	// cmd = "ps -ef | grep systemd | awk '{print $2}' | grep -v grep";
	// cmd = "echo \'$PATH$USER\'";
	// cmd = "echo \"$USER\"";
	// printf("Command Print: %s\n", cmd);
	// parsing_process(cmd);
	execution_process(meta->head); 
	free_gc();
}

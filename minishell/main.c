#include "minishell.h"

int main(void)
{
	char	*cmd;
	// t_token	*tmp;
	// cmd = readline("Minishell>> ");
	init_meta();
	cmd = "echo \"\"Hello World $USER I like it to test parsing!\'\' && ls /";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd);
	free_gc();
}

#include "minishell.h"

int main(void)
{
	t_meta	meta;
	char	*cmd;
	// t_token	*tmp;

	// cmd = readline("Minishell>> ");

	init_meta();


	cmd = "ls -l | grep a && ls / | awk {$1} || ls -l | grep b";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd, &meta);
}

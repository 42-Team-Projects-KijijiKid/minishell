#include "parsing.h"

int main(void)
{
	t_meta	meta;
	char	*cmd;
	// t_token	*tmp;

	// cmd = readline("Minishell>> ");
	meta.layer_1 = NULL;
	meta.layer_2 = NULL;
	meta.layer_3 = NULL;
	cmd = "ls -l | grep a && ls / | awk {$1} || ls -l | grep b";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd, &meta);
}

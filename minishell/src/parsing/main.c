#include "parsing.h"

int main(void)
{
	t_meta	meta;
	char	*cmd;
	t_token	*tmp;

	// cmd = readline("Minishell>> ");
	cmd = "echo \"Hello World\" | grep a && make re || echo \"I like the way BASH works\" | ls -a";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd, &meta);
}

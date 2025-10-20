#include "parsing.h"

int main(void)
{
	t_meta	meta;
	char	*cmd;
	t_token	*tmp;

	cmd = readline("Minishell>> ");
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd, &meta);
}

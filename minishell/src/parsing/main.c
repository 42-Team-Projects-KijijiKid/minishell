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
	cmd = "ls | grep && ls || wc";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd, &meta);
}

#include "parsing.h"

int main(void)
{
	t_meta	meta;
	char	*cmd;
	t_token	*tmp;

	cmd = readline("Minishell>> ");
	printf("%s\n", cmd);
	tmp = create_tokens(cmd);
	
}

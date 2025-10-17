#include "parsing.h"

void	parsing_process(char *cmd, t_meta *meta)
{
	t_tmp_cmd_token	*head;
	head = create_tokens(cmd);
	while (head)
	{
		printf("Command Nodes: %s\n", head->value);
		head = head->next;
	}
}

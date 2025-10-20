#include "parsing.h"

static t_token	*find_root(t_tmp_cmd_token *cmd_head)
{
	t_token	*root;


}

static t_token	*parse_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*root;
	t_token	*curr_token_head;

	curr_token_head = create_tokens(cmd_head);
	print_tokens(curr_token_head);
	exit (1);
	//Find Root Node(lowest Precedence, left-right associativity)
	root = find_root(cmd_head);

	return (root);
}

void	parsing_process(char *cmd, t_meta *meta)
{
	t_tmp_cmd_token	*cmd_head;
	t_token			*root_node;

	cmd_head = create_commands (cmd);
	root_node = parse_tokens(cmd_head);
}

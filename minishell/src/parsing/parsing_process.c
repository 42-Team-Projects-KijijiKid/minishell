#include "parsing.h"

static t_token	*parse_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*root;
	t_token	*token_head;

	token_head = create_tokens(cmd_head);
	// print_tokens(token_head);
	//Find Root Node(lowest Precedence, left-right associativity)
	root = find_root(token_head);
	printf("Root: %s\n", root->value);
	// build_ast(root);
	return (root);
}

void	parsing_process(char *cmd, t_meta *meta)
{
	t_tmp_cmd_token	*cmd_head;
	t_token			*root_node;

	cmd_head = create_commands (cmd);
	//Returns the root node 
	meta->head = parse_tokens(cmd_head);
	
}

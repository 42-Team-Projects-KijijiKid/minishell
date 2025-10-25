#include "parsing.h"

static t_token	*parse_tokens(t_tmp_cmd_token *cmd_head, t_meta *meta)
{
	t_token	*root;
	t_token	*token_head;

	token_head = create_tokens(cmd_head, meta);
	// print_tokens(token_head);
	//Find Root Node(lowest Precedence, left-right associativity)
	root = find_root(token_head);
	printf("Root: %s\n", root->value);
	build_ast(root);
	return (root);
}

void	parsing_process(char *cmd, t_meta *meta)
{
	t_tmp_cmd_token	*cmd_head;

	cmd_head = create_commands (cmd, meta);
	meta->head = parse_tokens(cmd_head, meta);
	syntax_errors(meta->head, meta, 0);
	print_ast_structure(meta->head, 0);
	free_layer(meta->layer_2);
	free_layer(meta->layer_3);
}

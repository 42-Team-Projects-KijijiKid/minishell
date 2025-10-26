#include "parsing.h"

static t_token	*parse_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*root;
	t_token	*token_head;

	token_head = create_tokens(cmd_head);
	// print_tokens(token_head);
	//Find Root Node(lowest Precedence, left-right associativity)
	root = find_root(token_head);
	build_ast(root);
	return (root);
}

void	parsing_process(char *cmd)
{
	t_tmp_cmd_token	*cmd_head;
	t_meta			*meta;

	meta = get_meta();
	cmd_head = create_commands (cmd);
	meta->head = parse_tokens(cmd_head);
	// check_syntax(meta->head); can we do before everything so not good here
	// expand_tokens(meta->head);
	print_ast_structure(meta->head, 0, false);
}

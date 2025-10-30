#include "parsing.h"

static t_token	*parse_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*root;
	t_token	*token_head;

	token_head = create_tokens(cmd_head);
	set_redirections(token_head);
	root = find_root(token_head);
	build_ast(root);
	return (root);
}

void	parsing_process(char *cmd)
{
	t_tmp_cmd_token	*cmd_head;
	t_meta			*meta;

	check_quotes(cmd);
	meta = get_meta();
	cmd_head = create_commands(cmd);
	meta->head = parse_tokens(cmd_head);
	expand_process(meta->head);
	print_ast_structure(meta->head, 0, false);
}

#include "../../inc/minishell.h"

void	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;

	validate_quote_pairs(input);
	shell = minishell_get();
	manager.head_token = tokenize(input);
	tokens_validate(manager.head_token);
	manager.root_token = find_root(manager.head_token);
	manager.root_node = token_to_tree_node(manager.root_token);
	shell->tree_root = manager.root_node;
	tree_build(&manager, 1);
	// print_ast_structure(manager.root_node, 0, false);
}

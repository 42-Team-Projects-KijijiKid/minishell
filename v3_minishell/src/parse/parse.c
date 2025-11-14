#include "../../inc/minishell.h"

void	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;

	validate_quote_pairs(input);
	shell = minishell_get();
	manager.head_token = tokenize(input);
	// print_tokens(manager.head_token, "tree-root head token");
	tokens_validate(manager.head_token);
	manager.root_token = find_root(manager.head_token);
	// print_tokens(manager.root_token, "tree-root root token");
	manager.root_node = token_to_tree_node(manager.root_token);
	// debug_ast("Root node", __FILE__, __LINE__, manager.root_node);
	shell->tree_root = manager.root_node;
	tree_build(&manager, 1);
	// printf("\n\n\n\n\n");
	// print_ast_structure(shell->tree_root, 0, false);
}

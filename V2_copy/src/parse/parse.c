#include "../../inc/minishell.h"

void	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;

	///Also add Syntax check for parenthesis
	validate_quote_pairs(input);
	shell = minishell_get();
	manager.head_token = tokenize(input);
	manager.root_token = find_root(manager.head_token);
	manager.root_node = token_to_tree_node(manager.root_token);
	shell->tree_root = manager.root_node;
	tree_build(&manager);
	//expand(shell->tree_root); // preliminary implementation; waiting for adjusted version from Mateo
	expand_process(shell->tree_root);
	print_ast_structure(shell->tree_root, 0, false);
}

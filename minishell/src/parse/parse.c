#include "../../inc/minishell.h"

void	minishell_parse(char *input)
{
	t_token			*token_head;
	t_minishell		*shell;
	t_build_manager	manager;

	validate_quote_pairs(input);
	shell = minishell_get();
	token_head = tokens_seperate(input);
	tokens_process(token_head);
	manager.head_token = token_head;
	manager.root_token = find_root(token_head);
	manager.root_node = token_to_tree_node(manager.root_token);
	tree_build(&manager);
	shell->tree_root = manager.root_node;
	expand(shell->tree_root); // preliminary implementation; waiting for adjusted version from Mateo
	print_ast_structure(shell->tree_root, 0, false);
}

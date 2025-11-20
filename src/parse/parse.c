#include "../../inc/minishell.h"

int	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;
	int				validate_rtn;

	shell = minishell_get();
	validate_rtn = validate_quote_pairs(input);
	if (validate_rtn != 0)
	{
		shell->last_exit_status = validate_rtn;
		return (shell->last_exit_status);
	}
	manager.head_token = tokenize(input);
	tokens_validate(manager.head_token);
	manager.root_token = find_root(manager.head_token);
	manager.root_node = token_to_tree_node(manager.root_token);
	shell->tree_root = manager.root_node;
	tree_build(&manager, 1);
	print_ast_structure(manager.root_node, 0, false);
	return (0);
}

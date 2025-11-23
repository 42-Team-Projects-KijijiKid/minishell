#include "../../inc/minishell.h"

int	*get_error_code(void)
{
	static int	error_code = 0;

	return (&error_code);
}

int	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;
	int				validate_rtn;

	shell = minishell_get();
	validate_quote_pairs(input);
	if (*get_error_code())
		return (*get_error_code());
	manager.head_token = tokenize(input);
	// print_tokens(manager.head_token, "Head");
	tokens_validate(manager.head_token);
	if (*get_error_code())
		return (*get_error_code());
	manager.root_token = find_root(manager.head_token);
	if (*get_error_code())
		return (*get_error_code());
	// print_tokens(manager.root_token, "Root");
	manager.root_node = token_to_tree_node(manager.root_token);
	// print_ast_structure(manager.root_node, 0, false);
	shell->tree_root = manager.root_node;
	tree_build(&manager);
	// print_ast_structure(manager.root_node, 0, false);
	return (shell->last_exit_status);
}

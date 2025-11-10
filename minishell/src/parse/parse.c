#include "../../inc/minishell.h"

t_tree_node	*print_ast_structure(t_tree_node *root, int level, bool left)
{
	if (!root)
		return (NULL);
	print_ast_structure(root->right, level + 1, false);
	for (int i = 0; i < level; i++)
		printf("		");
	if (left)
		printf("L: ");
	else
		printf("R: ");
	if (level != 0)
		printf("-> ");
	if (root->sub)
		printf("SUBSH");
	if (root->args)
	{
		printf("[");
		while (*root->args)
		{
			printf("%s, ", *root->args);
			root->args++;
		}
		printf("]\n");
	}
	print_ast_structure(root->left, level + 1, true);
	return (root);
}

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
	// expand(shell->tree_root); // preliminary implementation; waiting for adjusted version from Mateo
	print_ast_structure(shell->tree_root, 0, false);
	exit (101);
}

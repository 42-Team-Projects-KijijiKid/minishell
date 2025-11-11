#include "minishell.h"

void	print_ast_structure(t_tree_node *root, int level, bool left)
{
	if (!root)
		return;
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
}

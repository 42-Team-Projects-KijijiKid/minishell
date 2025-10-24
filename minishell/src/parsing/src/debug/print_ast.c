#include "parsing.h"

void	print_ast_structure(t_token *root, int level)
{
	if (!root)
		return;

	print_ast_structure(root->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("	");
	if (level != 0)
		printf("-> ");
	printf("%s\n", root->value);
	print_ast_structure(root->left, level + 1);
}

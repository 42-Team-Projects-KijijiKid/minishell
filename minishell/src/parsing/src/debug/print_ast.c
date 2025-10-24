#include "parsing.h"

void	print_ast_structure(t_token *root, int level)
{
	if (!root)
		return;

	print_ast_structure(root->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("		");
	if (level != 0)
		printf("-> ");
	if (root->value)
			printf("%s\n", root->value);
	else
	{
		printf("[");
		while (*root->args_2d)
		{
			printf("%s, ", *root->args_2d);
			root->args_2d++;
		}
		printf("]\n");
	}
	print_ast_structure(root->left, level + 1);
}

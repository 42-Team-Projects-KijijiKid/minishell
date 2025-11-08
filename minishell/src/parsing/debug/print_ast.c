#include "parsing.h"

void	print_ast_structure(t_token *root, int level, bool left)
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
	if (root->type == SUBSHELL)
		printf("SUBSHELL\n");
	else if (root->args_2d)
	{
		printf("[");
		while (*root->args_2d)
		{
			printf("%s, ", *root->args_2d);
			root->args_2d++;
		}
		printf("]\n");
	}
	print_ast_structure(root->left, level + 1, true);
}

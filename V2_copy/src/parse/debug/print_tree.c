#include "minishell.h"

static void print_operator(e_tree_node_type type)
{
	if (type == AND_IF)
		printf("&&");
	else if (type == OR_IF)
		printf("||");
	else if (type == PIPE)
		printf("|");
}

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
	if (root->type != TEXT)
		print_operator(root->type);
	else
	{
		printf("[");
		while (*root->args)
		{
			printf("%s, ", *root->args);
			root->args++;
		}
		printf("]");
	}
	printf("\n");
	print_ast_structure(root->left, level + 1, true);
}

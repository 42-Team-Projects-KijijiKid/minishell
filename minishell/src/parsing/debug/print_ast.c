#include "parsing.h"

void	redir_type_print(t_redir_type type)
{
	if (type == IN_FD)
		printf("In");
	if (type == OUT_FD)
		printf("Out");
}

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
	if (root->redir_meta.head)
	{
		redir_type_print(root->redir_meta.head->type);
		printf("Fd: %d", root->redir_meta.head->fd);
	}
	if (root->args_2d)
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

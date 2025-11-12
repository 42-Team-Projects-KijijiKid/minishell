#include "minishell.h"

static void	print_redirects(t_tree_node *node)
{
	t_redirect_node	*redirect;

	redirect = node->redirect.head;
	while (redirect)
	{
		printf("%s -> ", redirect->file);
		redirect = redirect->next;
	}
}

static void print_operator(e_tree_node_type type)
{
	if (type == AND_IF)
		printf("&&");
	else if (type == OR_IF)
		printf("||");
	else if (type == PIPE)
		printf("|");
}

void	print_ast_structure(t_tree_node *node, int level, bool left)
{
	if (!node)
		return;
	print_ast_structure(node->right, level + 1, false);
	for (int i = 0; i < level; i++)
		printf("		");
	if (left)
		printf("L: ");
	else
		printf("R: ");
	if (level != 0)
		printf("-> ");
	if (node->sub)
		printf("SUBSH");
	if (node->type != TEXT)
		print_operator(node->type);
	else
	{
		printf("[");
		while (*node->args)
		{
			printf("%s, ", *node->args);
			node->args++;
		}
		printf("]");
		if (node->redirect.head)
			print_redirects(node);
	}
	printf("\n");
	print_ast_structure(node->left, level + 1, true);
}

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

static void	print_operator(t_tree_node_type type)
{
	if (type == AND_IF)
		printf("&&");
	else if (type == OR_IF)
		printf("||");
	else if (type == PIPE)
		printf("|");
}

static void	print_indent(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("        ");
		i++;
	}
}

static void	print_args_and_redirs(t_tree_node *node)
{
	char	**tmp;

	tmp = node->args;
	printf("[");
	while (*tmp)
	{
		printf("%s, ", *tmp);
		tmp++;
	}
	printf("]");
	if (node->redirect.head)
		print_redirects(node);
}

void	print_ast_structure(t_tree_node *node, int level, bool left)
{
	if (!node)
		return ;
	print_ast_structure(node->right, level + 1, false);
	print_indent(level);
	if (left)
		printf("Left: ");
	else
		printf("Right: ");
	if (level != 0)
		printf("-> ");
	if (node->sub)
		printf("SUBSH");
	if (node->type != TEXT)
		print_operator(node->type);
	else
		print_args_and_redirs(node);
	printf("\n");
	print_ast_structure(node->left, level + 1, true);
}

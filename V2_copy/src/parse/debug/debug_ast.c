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

void	debug_ast(char *prefix ,char *file, int line, t_tree_node *node)
{
	printf("\033[31;3m%s: ", prefix);
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
		printf("] ");
	}
	printf("%s, %d\033[0m\n", file, line);
}

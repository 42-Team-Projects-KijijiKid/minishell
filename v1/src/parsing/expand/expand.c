#include "../../../inc/minishell.h"

/// @brief Processes a single argument string for expansion
/// Handles single quotes, double quotes, and bare variables
/// @param argument Single argument string from args array
/// @return Processed string with appropriate expansion
static char	*process_single_argument(char *argument)
{
	if (*argument == '\'')
		return (extract_single_quoted_content(argument));
	else if (*argument == '\"')
		return (extract_double_quoted_with_expansion(argument));
	else if (*argument == '$')
		return (expand_standalone_variable(argument));
	return (argument);
}

/// @brief Processes all arguments in a node for expansion
/// Iterates through args array and expands each one
/// @param node Tree node containing arguments to expand
void	expand_arguments_in_node(t_tree_node *node)
{
	char	**original_head;

	original_head = node->args;
	while (*node->args)
	{
		*node->args = process_single_argument(*node->args);
		node->args++;
	}
	node->args = original_head;
}

/// @brief Recursively traverses tree and expands variables
/// Only processes TEXT nodes with multiple arguments
/// @param node Current tree node to process
void	expand(t_tree_node *node)
{
	if (!node)
		return ;
	if (node->type == TEXT)
	{
		if (*node->args && node->args[1])
			expand_arguments_in_node(node);
	}
	expand(node->left);
	expand(node->right);
}

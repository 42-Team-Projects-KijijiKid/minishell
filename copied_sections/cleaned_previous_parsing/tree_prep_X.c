#include "../../../inc/minishell.h"

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
static e_tree_node_type	get_tree_node_type(t_token *token)
{
	int	len;

	len = ft_strlen(*token->args);
	char *a = *token->args;
	if (ft_strncmp(token->args[0], "|", len) == 0)
		return (PIPE);
	else if (ft_strncmp(token->args[0], "(", len) == 0)
		return (LPAREN);
	else if (ft_strncmp(token->args[0], ")", len) == 0)
		return (RPAREN);
	else if (ft_strncmp(token->args[0], "&&", len) == 0)
		return (AND_IF);
	else if (ft_strncmp(token->args[0], "||", len) == 0)
		return (OR_IF);
	else if (ft_strncmp(token->args[0], "<", len) == 0)
		return (LESS);
	else if (ft_strncmp(token->args[0], ">", len) == 0)
		return (GREAT);
	else if (ft_strncmp(token->args[0], ">>", len) == 0)
		return (DGREAT);
	else if (ft_strncmp(token->args[0], "<<", len) == 0)
		return (DLESS);
	else
		return (TEXT);
}

/// @brief Nulls every value of the token.
/// Safety wise.
/// @param token 
static void	initialize_tree_node(t_tree_node *node)
{
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->back = NULL;
	node->sub = false;
	node->redirect.head = NULL;
	node->redirect.tail = NULL;
	node->redirect.size = 0;
}

/// @brief Turns the command linked list
/// into the nodes for the parsing
/// also in a linked list like way
/// (always assigned on left)
/// Token type is already assigned here.
/// @param head_token 
/// @return 
t_tree_node	*tree_prep(t_token *head_token)
{
	t_tree_node	*head_node;
	t_tree_node	*tree_node;
	t_tree_node	*prev_node;
	t_minishell	*shell;

	shell = minishell_get();
	head_node = NULL;
	prev_node = NULL;
	while (head_token)
	{
		tree_node = ft_malloc(sizeof(t_tree_node), TEMPORARY);
		initialize_tree_node(tree_node);
		tree_node->type = get_tree_node_type(head_token);
		tree_node->args = head_token->args;
		if (prev_node)
			prev_node->left = tree_node;
		else
			head_node = tree_node;
		tree_node->sub = false;
		tree_node->back = prev_node;
		prev_node = tree_node;
		head_token = head_token->prev;
	}
	tree_node->left = NULL;
	return (head_node);
}

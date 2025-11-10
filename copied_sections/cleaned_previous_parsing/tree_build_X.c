#include "../../../inc/minishell.h"

static t_tree_node *get_last_node(t_tree_node *head)
{
	while (head && head->left)
		head = head->left;
	return (head);
}

/// @brief Erase the parenthesis and sets the 
/// root of the parenthesis a flag for execution
/// to know this has to run
/// since here in a subshell
/// @param head 
static void remove_outer_parentheses(t_tree_node **head)
{
	int		paren_depth;
	t_tree_node	*current;
	t_tree_node	*opening_paren;
	t_tree_node	*closing_paren;
	t_tree_node *subshell_root;

	if (!head || !*head || (*head)->type != LPAREN)
		return ;
	subshell_root = find_root((*head)->left);
	subshell_root->sub = true;
	paren_depth = 0;
	opening_paren = *head;
	current = opening_paren;
	closing_paren = NULL;
	while (current)
	{
		if (current->type == LPAREN)
			++paren_depth;
		else if (current->type == RPAREN && --paren_depth == 0)
		{
			closing_paren = current;
			break ;
		}
		current = current->left;
	}
	if (closing_paren && closing_paren == get_last_node(opening_paren))
	{
		*head = opening_paren->left;
		if (*head)
			(*head)->back = NULL;
	}
}

/// @brief Splits linked list in two parts, 
/// left and right site of operator.
void	split_at_operator(t_tree_node *operator_node, t_tree_node *left_sublist, t_tree_node *right_sublist)
{
	if (operator_node->back)
	{
		left_sublist->left = NULL;
		operator_node->back = NULL;
	}
	if (operator_node->left)
	{
		right_sublist->back = NULL;
		operator_node->left = NULL;
	}
}

/// @brief Builds ast recursively
/// Always evaluates root then splits linked list
/// at the current root and reevaluates the root
/// @param root pointer to current root
// modified build_ast: strip outer parens on each side before finding subtree roots
void build_ast(t_tree_node *current_root)
{
	t_tree_node *left_sublist;
	t_tree_node *right_sublist;

	if (!current_root)
		return;
	left_sublist = current_root->back;
	right_sublist = current_root->left;
	split_at_operator(current_root, left_sublist, right_sublist);
	while (left_sublist && left_sublist->back)
		left_sublist = left_sublist->back;
	remove_outer_parentheses(&left_sublist);
	remove_outer_parentheses(&right_sublist);
	if (left_sublist)
		current_root->left = find_root(left_sublist);
	else
		current_root->left = NULL;
	if (right_sublist)
		current_root->right = find_root(right_sublist);
	else
		current_root->right = NULL;
	build_ast(current_root->left);
	build_ast(current_root->right);
}

t_tree_node	*tree_build(t_token *head_token)
{
	t_tree_node	*root;
	t_tree_node	*head_node;

	head_node = tree_prep(head_token);
	prep_redirections(head_node);
	root = find_root(head_node);
	build_ast(root);
	return (root);
}

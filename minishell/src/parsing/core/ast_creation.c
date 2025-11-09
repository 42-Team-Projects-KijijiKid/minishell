#include "parsing.h"

// helpers
static t_token *list_tail(t_token *h)
{
	while (h && h->left)
		h = h->left;
	return (h);
}

/// @brief Erase the parenthesis and sets the 
/// root of the parenthesis a flag for execution
/// to know this has to run
/// since here in a subshell
/// @param head 
static void strip_outer_parens(t_token **head)
{
	int		depth;
	t_token	*cur;
	t_token	*open;
	t_token	*close;
	t_token *root;

	if (!head || !*head || (*head)->type != LPAREN)
		return ;
	root = find_root((*head)->left);
	root->sub = true;
	depth = 0;
	open = *head;
	cur = open;
	close = NULL;
	while (cur)
	{
		if (cur->type == LPAREN)
			++depth;
		else if (cur->type == RPAREN && --depth == 0)
		{
			close = cur;
			break ;
		}
		cur = cur->left;
	}
	if (close && close == list_tail(open))
	{
		*head = open->left;
		if (*head)
			(*head)->back = NULL;
	}
}

/// @brief Splits linked list in two parts, 
/// left and right site of operator.
void	assign_subtrees(t_token *root, t_token *pre_head, t_token *post_head)
{
	if (root->back)
	{
		pre_head->left = NULL;
		root->back = NULL;
	}
	if (root->left)
	{
		post_head->back = NULL;
		root->left = NULL;
	}
}

/// @brief Builds ast recursively
/// Always evaluates root then splits linked list
/// at the current root and reevaluates the root
/// @param root pointer to current root
// modified build_ast: strip outer parens on each side before finding subtree roots
void build_ast(t_token *root)
{
	t_token *pre_head;
	t_token *post_head;

	if (!root)
		return;
	pre_head = root->back;
	post_head = root->left;
	assign_subtrees(root, pre_head, post_head);
	while (pre_head && pre_head->back)
		pre_head = pre_head->back;
	strip_outer_parens(&pre_head);
	strip_outer_parens(&post_head);
	if (pre_head)
		root->left = find_root(pre_head);
	else
		root->left = NULL;
	if (post_head)
		root->right = find_root(post_head);
	else
		root->right = NULL;
	build_ast(root->left);
	build_ast(root->right);
}

#include "parsing.h"

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
void build_ast(t_token *root)
{
	t_token *pre_head;
	t_token *post_head;

	pre_head = NULL;
	post_head = NULL;
	if (!root)
		return ;
	pre_head = root->back;
	post_head = root->left;
	assign_subtrees(root, pre_head, post_head);
	if (pre_head)
		root->left = find_root_reversed(pre_head);
	else
		root->left = NULL;
	if (post_head)
		root->right = find_root(post_head);
	else 
		root->right = NULL;
	build_ast(root->left);
	build_ast(root->right);
}

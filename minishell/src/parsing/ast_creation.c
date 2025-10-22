#include "parsing.h"

void build_ast(t_token *root)
{
    t_token *pre_head;
    t_token *post_head;

	pre_head = NULL;
	post_head = NULL;
	if (!root)
        return;
    // Detach left side (tokens before `root`)
    if (root->back)
	{
        pre_head = root->back;
        pre_head->left = NULL;
        root->back = NULL;
    }
    // Detach right side (tokens after `root`)
    if (root->left)
	{
        post_head = root->left;
        post_head->back = NULL;
        root->left = NULL;
    }
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


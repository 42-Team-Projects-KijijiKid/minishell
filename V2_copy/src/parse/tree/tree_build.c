#include "../../../inc/minishell.h"

static t_token	*get_left_tokens(t_token	*root)
{
	t_token	*node;

	node = root->prev;
	root->prev = NULL;
	node->next = NULL;
	while (node->prev)
		node = node->prev;
	return (node);
}

static t_token	*get_right_tokens(t_token	*root)
{
	t_token	*node;

	if (root->next)
	{
		node = root->next;
		node->prev = NULL;
		root->next = NULL;
		return (node);
	}
	return (NULL);
}

static t_build_manager	*build_manager(t_token *token, t_build_manager *manager)
{
	manager->head_token = token;
	manager->root_token = find_root(token);
	manager->root_node = token_to_tree_node(manager->root_token);
	return (manager);
}

void	tree_build(t_build_manager *manager)
{
	t_token			*left;
	t_token			*right;
	t_build_manager	left_manager;
	t_build_manager	right_manager;

	if (manager->root_token->type == TEXT)
	{
		tree_redirects(manager);
		return ;
	}
	// tree_subshells(manager);
	left = get_left_tokens(manager->root_token);
	right = get_right_tokens(manager->root_token);
	build_manager(left, &left_manager);
	build_manager(right, &right_manager);
	manager->root_node->left = left_manager.root_node;
	manager->root_node->right = right_manager.root_node;
	tree_build(&left_manager);
	tree_build(&right_manager);
}

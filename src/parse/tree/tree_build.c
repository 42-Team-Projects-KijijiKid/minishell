#include "../../../inc/minishell.h"

static t_token	*get_left_tokens(t_token *head, t_token *root)
{
	root->prev->next = NULL;
	return (head);
}

static t_token	*get_right_tokens(t_token *root)
{
	root = root->next;
	root->prev = NULL;
	return (root);
}

void	build_left_subtree(t_build_manager *manager)
{
	t_build_manager	left_manager;

	left_manager.head_token = get_left_tokens(\
		manager->head_token, manager->root_token);
	left_manager.root_token = find_root(left_manager.head_token);
	if (minishell_get()->last_exit_status)
		return ;
	left_manager.root_node = token_to_tree_node(left_manager.root_token);
	manager->root_node->left = left_manager.root_node;
	tree_build(&left_manager);
}

void	build_right_subtree(t_build_manager *manager)
{
	t_build_manager	right_manager;

	right_manager.head_token = get_right_tokens(manager->root_token);
	right_manager.root_token = find_root(right_manager.head_token);
	if (minishell_get()->last_exit_status)
		return ;
	right_manager.root_node = token_to_tree_node(right_manager.root_token);
	manager->root_node->right = right_manager.root_node;
	tree_build(&right_manager);
}

void	tree_build(t_build_manager *manager)
{
	tokens_validate(manager->head_token);
	if (minishell_get()->last_exit_status)
		return ;
	tree_subshells(manager);
	if (manager->root_token->type == TEXT)
	{
		tree_redirects(manager);
		return ;
	}
	build_left_subtree(manager);
	build_right_subtree(manager);
}

// #include "../../../inc/minishell.h"

// static t_token	*get_left_tokens(t_token *head, t_token *root)
// {
// 	root->prev->next = NULL;
// 	if (!head)
// 		ft_error("invalid input", __FILE__, __LINE__, 1000);
// 	return (head);
// }

// static t_token	*get_right_tokens(t_token *root)
// {
// 	if (!root->next)
// 		ft_error("invalid input", __FILE__, __LINE__, 1000);
// 	root = root->next;
// 	root->prev = NULL;
// 	return (root);
// }

// void	build_left_subtree(t_build_manager *manager, int lvl)
// {
// 	t_build_manager	left_manager;

// 	left_manager.head_token = get_left_tokens(manager->head_token, manager->root_token);
// 	tokens_validate(left_manager.head_token);
// 	print_tokens(left_manager.head_token, "Left-Head");
// 	left_manager.root_token = find_root(left_manager.head_token);
// 	print_tokens(left_manager.root_token, "Left-Root");
// 	left_manager.root_node = token_to_tree_node(left_manager.root_token);
// 	manager->root_node->left = left_manager.root_node;
// 	tree_build(&left_manager, lvl + 1);
// }

// void	build_right_subtree(t_build_manager *manager, int lvl)
// {
// 	t_build_manager	right_manager;

// 	right_manager.head_token = get_right_tokens(manager->root_token);
// 	tokens_validate(right_manager.head_token);
// 	print_tokens(right_manager.head_token, "Right-Head");
// 	right_manager.root_token = find_root(right_manager.head_token);
// 	print_tokens(right_manager.root_token, "Right-Root");
// 	right_manager.root_node = token_to_tree_node(right_manager.root_token);
// 	manager->root_node->right = right_manager.root_node;
// 	print_ast_structure(manager->root_node, 0, false);
// 	tree_build(&right_manager, lvl + 1);
// }

// void	tree_build(t_build_manager *manager, int lvl)
// {
// 	printf("Level: %d\n", lvl);
// 	tree_subshells(manager);
// 	if (manager->root_token->type == TEXT)
// 	{
// 		tree_redirects(manager);
// 		return ;
// 	}
// 	build_left_subtree(manager, lvl);
// 	build_right_subtree(manager, lvl);
// }

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

void	build_left_subtree(t_build_manager *manager, int lvl)
{
	t_build_manager	left_manager;

	left_manager.head_token = get_left_tokens(manager->head_token, manager->root_token);
	left_manager.root_token = find_root(left_manager.head_token);
	left_manager.root_node = token_to_tree_node(left_manager.root_token);
	manager->root_node->left = left_manager.root_node;
	tree_build(&left_manager, lvl + 1);
}

void	build_right_subtree(t_build_manager *manager, int lvl)
{
	t_build_manager	right_manager;

	right_manager.head_token = get_right_tokens(manager->root_token);
	right_manager.root_token = find_root(right_manager.head_token);
	right_manager.root_node = token_to_tree_node(right_manager.root_token);
	manager->root_node->right = right_manager.root_node;
	tree_build(&right_manager, lvl + 1);
}

void	tree_build(t_build_manager *manager, int lvl)
{
	tokens_validate(manager->head_token);
	tree_subshells(manager);
	if (manager->root_token->type == TEXT)
	{
		tree_redirects(manager);
		return ;
	}
	build_left_subtree(manager, lvl);
	build_right_subtree(manager, lvl);
}

#include "../../../inc/minishell.h"

static void	handle_subshell_parentheses(t_build_manager *manager)
{
	t_token	*last;

	last = get_last_node(manager->head_token);
	if (manager->head_token->type == LPAREN && last && last->type == RPAREN)
	{
		manager->root_node->sub = true;
		remove_outer_parentheses(&(manager->head_token));
		manager->root_token = find_root(manager->head_token);
		if (manager->root_token)
			manager->root_node = token_to_tree_node(manager->root_token);
		else
		{
			// Wieso hier ohne return(aber bei den andern mit)
			ft_error("tree_build: failed to reassign root after removing parentheses", \
				__FILE__, __LINE__, 71);
		}
	}
}

static void	build_left_subtree(t_build_manager *manager)
{
	t_build_manager	left;

	left.head_token = get_left_tokens(&(manager->root_token));
	if (left.head_token)
	{
		left.root_token = find_root(left.head_token);
		if (left.root_token)
		{
			left.root_node = token_to_tree_node(left.root_token);
			manager->root_node->left = left.root_node;
			tree_build(&left);
		}
	}
}

static void	build_right_subtree(t_build_manager *manager)
{
	t_build_manager	right;

	right.head_token = get_right_tokens(&(manager->root_token));
	if (right.head_token)
	{
		right.root_token = find_root(right.head_token);
		if (right.root_token)
		{
			right.root_node = token_to_tree_node(right.root_token);
			manager->root_node->right = right.root_node;
			tree_build(&right);
		}
	}
}

void	tree_build(t_build_manager *manager)
{
	if (!manager || !manager->head_token || !manager->root_token || \
		!manager->root_node)
	{
		//Warum hier mit return
		ft_error("tree_build: invalid build manager", __FILE__, __LINE__, 71);
		return ;
	}
	//Warum ?
	if (manager->root_token->type == TEXT || \
		manager->head_token == manager->root_token)
		return ;
	if (is_redirect(manager->root_token->type))
	{
		build_redirection_tree(manager);
		return ;
	}
	handle_subshell_parentheses(manager);
	if (!manager->root_token)
		return ;
	build_left_subtree(manager);
	build_right_subtree(manager);
}

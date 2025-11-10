#include "../../../inc/minishell.h"

static void	remove_first_token(t_token **root)
{
	t_token	*temp;

	if (!root || !*root)
		return ;
	if (!(*root)->next)
	{
		*root = NULL;
		return ;
	}
	temp = *root;
	*root = (*root)->next;
	(*root)->prev = NULL;
}

static void	process_redirect_target(t_build_manager *manager)
{
	if (!manager->head_token->next)
	{
		ft_error("build_redirect_chain: missing target after redirect", \
			__FILE__, __LINE__, 71);
		return ;
	}
	manager->root_node->left = token_to_tree_node(manager->head_token->next);
	remove_first_token(&(manager->head_token));
	remove_first_token(&(manager->head_token));
}

static void	setup_next_redirect(t_build_manager *manager, \
	t_build_manager *next, t_token *cmd)
{
	next->head_token = manager->head_token;
	next->root_token = manager->head_token;
	next->root_node = (t_tree_node *)ft_malloc(sizeof(t_tree_node), TEMPORARY);
	initialize_tree_node(next->root_node);
	manager->root_node->right = next->root_node;
	build_redirect_chain(next, cmd);
}

void	build_redirect_chain(t_build_manager *manager, t_token *cmd)
{
	t_build_manager	next;

	if (!manager || !manager->root_node)
	{
		ft_error("build_redirect_chain: invalid build manager", \
			__FILE__, __LINE__, 71);
		return ;
	}
	if (!manager->head_token || !is_redirect(manager->head_token->type))
	{
		manager->root_node->right = token_to_tree_node(cmd);
		return ;
	}
	process_redirect_target(manager);
	if (!manager->head_token || !is_redirect(manager->head_token->type))
	{
		manager->root_node->right = token_to_tree_node(cmd);
		return ;
	}
	setup_next_redirect(manager, &next, cmd);
}

void	build_redirection_tree(t_build_manager *manager)
{
	t_token	*cmd;

	if (!validate_redirection_tree(manager))
		return ;
	cmd = manager->head_token;
	remove_first_token(&(manager->head_token));
	if (!manager->head_token || manager->head_token != manager->root_token)
	{
		ft_error("build_redirection_tree: command not directly before first redirect", \
			__FILE__, __LINE__, 71);
		return ;
	}
	manager->root_node->left = token_to_tree_node(manager->head_token->next);
	remove_first_token(&(manager->head_token));
	remove_first_token(&(manager->head_token));
	build_redirect_chain(manager, cmd);
}

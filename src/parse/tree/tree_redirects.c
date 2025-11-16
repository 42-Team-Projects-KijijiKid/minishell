#include "../../../inc/minishell.h"

bool	is_redirect(e_tree_node_type type)
{
	if (type == DGREAT)
		return (true);
	else if (type == DLESS)
		return (true);
	else if (type == GREAT)
		return (true);
	else if (type == LESS)
		return (true);
	return (false);
}

void	tree_redirects(t_build_manager *manager)
{
	t_token			*node;
	t_redirect_node	*redirect;

	if (!manager->head_token->next)
		return ;
	node = manager->head_token->next;
	redirect = NULL;
	if (node && is_redirect(node->type))
		redirect = (t_redirect_node *)fti_malloc(sizeof(t_redirect_node), TEMPORARY);
	while (node && is_redirect(node->type))
	{
		if (manager->root_node->redirect.head == NULL)
			manager->root_node->redirect.head = redirect;
		redirect->type = node->type;
		redirect->file = node->next->args[0];
		redirect->next = NULL;
		node = node->next;
		node = node->next;
		if (node && is_redirect(node->type))
			redirect->next = (t_redirect_node *)fti_malloc(sizeof(t_redirect_node), TEMPORARY);
		redirect = redirect->next;
	}
}

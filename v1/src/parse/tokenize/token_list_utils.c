#include "../../../inc/minishell.h"

t_token *get_last_node(t_token *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

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

t_token	*get_left_tokens(t_token **root)
{
	t_token	*current_token;

	if (!root || !*root || !(*root)->prev)
		return (NULL);
	current_token = *root;
	while (current_token && current_token->prev)
		current_token = current_token->prev;
	(*root)->prev->next = NULL;
	(*root)->prev = NULL;
	return (current_token);
}

t_token	*get_right_tokens(t_token **root)
{
	t_token	*current_token;

	if (!root || !*root || !(*root)->next)
		return (NULL);
	current_token = (*root)->next;
	(*root)->next = NULL;
	current_token->prev = NULL;
	return (current_token);
}

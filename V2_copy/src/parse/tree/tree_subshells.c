#include "../../../inc/minishell.h"

void	tree_subshells(t_build_manager *manager)
{
	t_token	*last;
	t_token	*head;

	head = manager->head_token;
	last = head;
	while (last->next)
		last = last->next;	
	if (head->type == LPAREN && last->type == RPAREN)
	{
		if (head->next == last)
			ft_error("Empty paranthesis detected", __FILE__, __LINE__, 996);
		manager->root_node->sub = true;
		head = head->next;
		head->prev->next = NULL;
		head->prev = NULL;
		last = last->prev;
		last->next->prev = NULL;
		last->next = NULL;
	}
}

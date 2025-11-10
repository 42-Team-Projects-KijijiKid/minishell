#include "../../../inc/minishell.h"

t_tree_node	*token_to_tree_node(t_token *head_token)
{
	t_tree_node	*node;

	node = ft_malloc(sizeof(t_tree_node), TEMPORARY);
	initialize_tree_node(node);
	node->args = head_token->args;
	node->type = head_token->type;
	return (node);
}

void	remove_outer_parentheses(t_token **head)
{
	t_token	*last;

	if (!head || !*head)
		return ;
	last = get_last_node(*head);
	if ((*head)->type != LPAREN || last->type != RPAREN)
		return ;
	*head = (*head)->next;
	(*head)->prev = NULL;
	last->prev->next = NULL;
}

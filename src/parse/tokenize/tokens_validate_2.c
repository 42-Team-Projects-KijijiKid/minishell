#include "minishell.h"

bool	is_operator(t_tree_node_type type)
{
	if (type == AND_IF)
		return (true);
	else if (type == OR_IF)
		return (true);
	else if (type == PIPE)
		return (true);
	return (false);
}

int	count_token_type(t_token *token, t_tree_node_type type)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

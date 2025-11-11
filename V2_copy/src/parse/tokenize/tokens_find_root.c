#include "../../../inc/minishell.h"

static bool	check_precedence(e_tree_node_type before, e_tree_node_type current)
{
	if (current == TEXT)
		return (false); //text not an operator
	if (before == TEXT)
		return (true);
	if (before == current)
		return (true); //left associativity
	if (current == AND_IF || current == OR_IF)
		return (true);
	return (false);
}

/// @brief Skips in quotes so there operators
/// outside of quotes have always
/// higher precedence
/// @param token_head 
/// @return 
t_token	*find_root(t_token *token_head)
{
	t_token				*root;
	t_token				*start;
	e_tree_node_type	tmp_enum;
	int					depth;

	tmp_enum = TEXT;
	root = NULL;
	start = token_head;
	depth = 0;
	while (token_head)
	{
		if (token_head->type == LPAREN)
			++depth;
		else if (token_head->type == RPAREN)
			--depth;
		else if (depth == 0 && check_precedence(tmp_enum, token_head->type))
		{
			tmp_enum = token_head->type;
			root = token_head;
		}
		token_head = token_head->next;
	}
	if (!root)
		root = start;
	return (root);
}

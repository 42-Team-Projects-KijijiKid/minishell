#include "parsing.h"

static bool	compare_operator(t_token_enum before, t_token_enum current)
{
	if (current == 0)
		return (false); //text not an operator
	if (before == T_TEXT)
		return (true);
	if (before == current)
		return (true); //left associativity
	if (current == T_AND || current == T_OR)
		return (true);
	return (false);
}

t_token	*find_root(t_token *token_head)
{
	t_token			*root;
	t_token			*token_head_buff;
	t_token_enum	tmp_enum;

	tmp_enum = T_TEXT;

	root = NULL;
	token_head_buff = token_head;
	while (token_head->left)
	{
		if (compare_operator(tmp_enum, token_head->type))
		{
			tmp_enum = token_head->type;
			root = token_head;
		}
		token_head = token_head->left;
	}
	if (!root)
		root =	token_head_buff;
	return (root);
}

#include "parsing.h"

static bool	compare_operator(t_token_enum before, t_token_enum current)
{
	if (current == 0)
		return (false); //text not an operator
	if (before == TEXT)
		return (true);
	if (before == current)
		return (true); //left associativity
	if (current == AND_IF || current == OR_IF)
		return (true);
	return (false);
}

/// @brief Finds the rootnode going from left
/// to right when there are tokens with the 
/// same precedence left associvity 
/// @param token_head head of the token list
/// @return pointer to root token
t_token	*find_root(t_token *token_head)
{
	t_token			*root;
	t_token			*token_head_buff;
	t_token_enum	tmp_enum;
	bool			flag;

	tmp_enum = TEXT;
	root = NULL;
	token_head_buff = token_head;
	flag = true;
	while (token_head->left)
	{
		if (token_head->type == LPAREN)
			flag = false;
		if (compare_operator(tmp_enum, token_head->type) && flag)
		{
			tmp_enum = token_head->type;
			root = token_head;
		}
		if (token_head->type == RPAREN)
			flag = true;
		token_head = token_head->left;
	}
	if (!root)
		root =	token_head_buff;
	return (root);
}

/// @brief This is just when there are multiple levels 
/// of operators
/// to evaluate the left side of the root
/// @param token_head 
/// @return pointer to root
t_token	*find_root_reversed(t_token *token_head)
{
	t_token			*root;
	t_token_enum	tmp_enum;

	tmp_enum = TEXT;
	root = NULL;
	while (token_head->back)
	{
		if (compare_operator(tmp_enum, token_head->type))
		{
			tmp_enum = token_head->type;
			root = token_head;
		}
		token_head = token_head->back;
	}
	if (!root)
		root =	token_head;
	return (root);
}

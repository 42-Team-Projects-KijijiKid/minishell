#include "../../../inc/minishell.h"

static int	get_precedence(e_tree_node_type type)
{
	if (type == AND_IF ||  type == OR_IF)
		return (1);
	if (type == PIPE)
		return (2);
	if (type == TEXT)
		return (3);
	return (4);
}

static bool	check_precedence(e_tree_node_type before, e_tree_node_type current)
{
	int	prec_cur;
	int	prec_bef;

	prec_bef = get_precedence(before);
	prec_cur = get_precedence(current);
	if (prec_bef > prec_cur)
		return (true);
	if (prec_bef == prec_cur && prec_cur < 3)
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

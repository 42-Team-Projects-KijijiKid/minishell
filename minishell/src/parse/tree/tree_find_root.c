#include "../../../inc/minishell.h"

static int	get_precedence(e_tree_node_type type)
{
	if (type == OR_IF || type == AND_IF)
		return (1);
	if (type == PIPE)
		return (2);
	if (type == LESS || type == GREAT || type == DLESS || type == DGREAT)
		return (3);
	return (0);
}

static bool	check_node_precedence(e_tree_node_type previous_op, e_tree_node_type current_op)
{
	int	prev_prec;
	int	curr_prec;

	curr_prec = get_precedence(current_op);
	if (curr_prec == 0)
		return (false);
	prev_prec = get_precedence(previous_op);
	if (prev_prec == 0)
		return (true);
	if (curr_prec < prev_prec)
		return (true);
	if (curr_prec == prev_prec)
		return (true);
	return (false);
}

/// @brief Skips in quotes so there operators
/// outside of quotes have always
/// higher precedence
/// @param head_token 
/// @return 
t_token	*find_root(t_token *head_token)
{
	t_token				*root;
	t_token				*start;
	e_tree_node_type	tmp_enum;
	int					depth;

	if (head_token->type == RPAREN)
		return (NULL);
	tmp_enum = TEXT;
	root = NULL;
	start = head_token;
	depth = 0;
	while (head_token && head_token->next)
	{
		if (head_token->type == LPAREN)
			++depth;
		else if (head_token->type == RPAREN)
			--depth;
		else if (depth == 0 && check_node_precedence(tmp_enum, head_token->type))
		{
			tmp_enum = head_token->type;
			root = head_token;
		}
		head_token = head_token->next;
	}
	if (!root)
		root = start;
	return (root);
}

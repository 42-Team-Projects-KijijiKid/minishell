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

static bool	check_precedence(int prec_bef, e_tree_node_type current)
{
	int	prec_cur;

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
// t_token	*find_root(t_token *token_head)
// {
// 	t_token				*root;
// 	t_token				*start;
// 	e_tree_node_type	tmp_enum;
// 	int					depth;

// 	tmp_enum = TEXT;
// 	root = NULL;
// 	start = token_head;
// 	depth = 0;
// 	while (token_head)
// 	{
// 		if (token_head->type == LPAREN)
// 			++depth;
// 		else if (token_head->type == RPAREN)
// 			--depth;
// 		else if (depth == 0 && check_precedence(tmp_enum, token_head->type))
// 		{
// 			tmp_enum = token_head->type;
// 			root = token_head;
// 		}
// 		token_head = token_head->next;
// 	}
// 	if (!root)
// 		root = start;
// 	return (root);
// }

t_token	*get_last_token(t_token *node)
{
	while (node->next)
		node = node->next;
	return (node);	
}

// int	count_subshells(t_token	*token)
// {
// 	int		subshells;

// 	subshells = 0;
// 	while (token)
// 	{
// 		if (token->type == LPAREN)
// 		{
// 			while (token->type != RPAREN)
// 			{
// 				if (!token->next)
// 					return (subshells);
// 				if (token->next->type == RPAREN)
// 					subshells++;
// 				token = token->next;
// 				if (!token)
// 					ft_error("Open paranthesis is never closed", __FILE__, __LINE__, 997);
// 			}
// 		}
// 		token = token->next;
// 	}
// 	printf("Subshell count: %d\n", subshells);
// 	return (subshells);
// }

int	count_subshells(t_token	*token)
{
	int		open_par;
	int		close_par;

	open_par = 0;
	close_par = 0;
	while (token)
	{
		if (token->type == LPAREN)
			open_par++;
		if (token->type == RPAREN)
			close_par++;
		token = token->next;
	}
	// if (open_par != close_par)
	//  	ft_error("uneven amount of parenthesis", __FILE__, __LINE__, 997);
	return (open_par);
}
t_token	*find_root(t_token *token_head)
{
	int		root_prec;
	t_token	*root;
	int		depth;
	
	if (count_subshells(token_head) == 1 && token_head->type == LPAREN \
		&& get_last_token(token_head)->type == RPAREN)
		token_head = token_head->next;
	root = token_head;
	root_prec = get_precedence(token_head->type);
	depth = 0;
	while (token_head)
	{
		if (token_head->type == LPAREN)
			++depth;
		else if (token_head->type == RPAREN)
			--depth;
		else if (depth == 0 && check_precedence(root_prec, token_head->type))
		{
			root_prec = get_precedence(token_head->type);
			root = token_head;
		}
		token_head = token_head->next;
	}
	return (root);
}

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

t_token	*find_root_without_subshell(t_token *head, t_token *tail)
{
	t_token	*root;
	int		root_prec;
	int		depth;

	// while (head && get_precedence(head->type) == 4)
	// 	head = head->next;
	root = head;
	root_prec = get_precedence(head->type);
	depth = 0;
	while (head && head != tail->next)
	{
		if (head->type == LPAREN)
			depth++;
		else if (head->type == RPAREN)
			depth--;
		else if (depth == 0 && check_precedence(root_prec, head->type))
		{
			root_prec = get_precedence(head->type);
			root = head;
		}
		head = head->next;
	}
	if (!root)
		ft_error("invalid token list", __FILE__, __LINE__, 998);
	return (root);
}

//  ( ( ( x ) (  x ) x ( x ) ) x ( x ) ) 
//  cs = 3
//  ce = 2
//  -+-+--+ = -1
//  pairs = 6
//  ( ( x ( ( ( x ) x ) x ) ) )
// count para at start
// count para at end
// count difference between opening and closing from (last at start) and (first at end)
// count at start - differnece

t_token	*find_root(t_token *head)
{
	t_token	*tail;
	int		cutoffs;

	tail = head;
	while (tail->next)
		tail = tail->next;
	cutoffs = count_subshell_cutoffs(head);
	printf("%p %d\n",head, cutoffs);
	while (cutoffs--)
	{
		head = head->next;
		// head->prev = NULL;
		tail = tail->prev;
		// tail->next = NULL;
	}
	return (find_root_without_subshell(head, tail));
}

// t_token	*find_root(t_token *head)
// {
// 	t_token	*tail;

// 	tail = head;
// 	while (tail->next)
// 		tail = tail->next;
// 	if (count_token_type(head, LPAREN) && head->type == LPAREN && tail->type == RPAREN)
// 	{
// 		head = head->next;
// 		head->prev = NULL;
// 		tail = tail->prev;
// 		tail->next = NULL;
// 		return (find_root(head));
// 	}
// 	else
// 		return (find_root_without_subshell(head));
// 	ft_error("Unexpected Error in find root function", __FILE__, __LINE__, 999);
// 	return (head);
// }



// static int	get_precedence(e_tree_node_type type)
// {
// 	if (type == AND_IF ||  type == OR_IF)
// 		return (1);
// 	if (type == PIPE)
// 		return (2);
// 	if (type == TEXT)
// 		return (3);
// 	return (4);
// }

// static bool	check_precedence(int prec_bef, e_tree_node_type current)
// {
// 	int	prec_cur;

// 	prec_cur = get_precedence(current);
// 	if (prec_bef > prec_cur)
// 		return (true);
// 	if (prec_bef == prec_cur && prec_cur < 3)
// 		return (true);
// 	return (false);
// }

// t_token	*get_last_token(t_token *node)
// {
// 	while (node->next)
// 		node = node->next;
// 	return (node);	
// }
// // }

// int	count_subshells(t_token	*token)
// {
// 	int		open_par;
// 	int		close_par;

// 	open_par = 0;
// 	close_par = 0;
// 	while (token)
// 	{
// 		if (token->type == LPAREN)
// 			open_par++;
// 		if (token->type == RPAREN)
// 			close_par++;
// 		token = token->next;
// 	}
// 	return (open_par);
// }
// t_token	*find_root(t_token *token_head)
// {
// 	int		root_prec;
// 	t_token	*root;
// 	int		depth;
	
// 	if (count_subshells(token_head) == 1 && token_head->type == LPAREN \
// 		&& get_last_token(token_head)->type == RPAREN)
// 		token_head = token_head->next;
// 	root = token_head;
// 	root_prec = get_precedence(token_head->type);
// 	depth = 0;
// 	while (token_head)
// 	{
// 		if (token_head->type == LPAREN)
// 			++depth;
// 		else if (token_head->type == RPAREN)
// 			--depth;
// 		else if (depth == 0 && check_precedence(root_prec, token_head->type))
// 		{
// 			root_prec = get_precedence(token_head->type);
// 			root = token_head;
// 		}
// 		token_head = token_head->next;
// 	}
// 	return (root);
// }

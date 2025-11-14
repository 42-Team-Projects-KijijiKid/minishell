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

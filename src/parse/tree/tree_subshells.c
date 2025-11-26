#include "../../../inc/minishell.h"

t_token	*get_last_token(t_token *node)
{
	while (node->next)
		node = node->next;
	return (node);
}

int	count_parenthesis_at_end(t_token *token)
{
	t_token	*last;
	int		count;

	last = get_last_token(token);
	count = 0;
	while (last && last->type == RPAREN)
	{
		count++;
		last = last->prev;
	}
	return (count);
}

int	count_parenthesis_at_start(t_token *token)
{
	int		count;

	count = 0;
	while (token && token->type == LPAREN)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_token	*get_final_before_parenthesis(t_token *token, bool reverse)
{
	if (reverse)
	{
		while (token->type == LPAREN)
			token = token->next;
	}
	else
	{
		token = get_last_token(token);
		while (token->type == RPAREN)
			token = token->prev;
	}
	return (token);
}

int	count_outer_subshells_reverse(t_token *token)
{
	int		depth;
	int		min_depth;
	bool	initial;
	t_token	*last;	

	initial = true;
	depth = 0;
	min_depth = INT_MAX;
	last = get_final_before_parenthesis(token, true);
	token = get_last_token(token);
	if (token == last)
		return (0);
	while (token && token != last->prev)
	{
		if (token->type != RPAREN)
			initial = false;
		if (token->type == LPAREN)
			depth--;
		else if (token->type == RPAREN)
			depth++;
		if (initial == false && min_depth > depth)
			min_depth = depth;
		token = token->prev;
	}
	if (last->type == RPAREN && initial)
		return (0);
	return (min_depth);
}

int	count_outer_subshells(t_token *token)
{
	int		depth;
	int		min_depth;
	bool	initial;
	t_token	*last;	

	initial = true;
	depth = 0;
	min_depth = INT_MAX;
	last = get_final_before_parenthesis(token, false);
	if (token == last)
		return (0);
	while (token && token != last->next)
	{
		if (token->type != LPAREN)
			initial = false;
		if (token->type == LPAREN)
			depth++;
		else if (token->type == RPAREN)
			depth--;
		if (initial == false && min_depth > depth)
			min_depth = depth;
		token = token->next;
	}
	if (last->type == LPAREN && initial)
		return (0);
	return (min_depth);
}

int	count_subshell_cutoffs(t_token *token)
{
	int	count;

	count = 0;
	if (count_parenthesis_at_start(token) >= count_parenthesis_at_end(token))
		count = count_outer_subshells(token);
	else
		count = count_outer_subshells_reverse(token);
	return (count);
}

void	tree_subshells(t_build_manager *manager)
{
	t_token	*last;
	t_token	*head;
	int		cutoffs;	

	head = manager->head_token;
	last = head;
	while (last->next)
		last = last->next;
	cutoffs = count_subshell_cutoffs(manager->head_token);
	manager->root_node->sub = cutoffs;
	while (cutoffs--)
	{
		head = head->next;
		head->prev = NULL;
		last = last->prev;
		last->next = NULL;
	}
	manager->head_token = head;
}

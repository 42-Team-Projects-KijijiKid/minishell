#include "../../../inc/minishell.h"

t_token	*get_last_token(t_token *node)
{
	while (node->next)
		node = node->next;
	return (node);	
}

int	count_edge_parenthesis(t_token *token, bool start)
{
	int		count;
	t_token	*last;

	count = 0;
	if (start)
	{
		while (token && token->type == LPAREN)
		{
			count++;
			token = token->next;
		}
	}
	else
	{
		last = get_last_token(token);
		while (last && last->type == RPAREN)
		{
			count++;
			last = last->prev;
		}
	}
	return (count);
}

t_token	*get_terminator(t_token *token, bool reverse)
{
	
	if (reverse)
	{
		while (token->type == LPAREN)
			token = token->next;
		token = token->prev;
	}
	else
	{
		token = get_last_token(token);
		while (token->type == RPAREN)
			token = token->prev;
		token = token->next;
	}
	return (token);
}

int	count_outer_subshells_reverse(t_token *token)
{
	bool	initial;
	int		depth;
	int		min_depth;
	t_token	*terminator;

}

int	count_outer_subshells(t_token *token)
{
	bool	initial;
	int		depth;
	int		min_depth;
	t_token	*terminator;

	initial = true;
	depth = 0;
	min_depth = INT_MAX;
	terminator = get_terminator(token, false);
	while ()
	{
		
	}
}

int	count_subshell_cutoffs(t_token *token)
{
	int	count;
	int	start;
	int	end;

	count = 0;
	start = count_edge_parenthesis(token, true);
	end = count_edge_parenthesis(token, false);
	if (start >= end)
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

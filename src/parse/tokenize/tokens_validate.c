#include "../../../inc/minishell.h"

bool	is_operator(t_tree_node_type type)
{
	if (type == AND_IF)
		return (true);
	else if (type == OR_IF)
		return (true);
	else if (type == PIPE)
		return (true);
	return (false);
}

int	count_token_type(t_token *token, t_tree_node_type type)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

bool	validate_subshells(t_token *token)
{
	int	depth;
	int	open;

	open = count_token_type(token, LPAREN);
	if (open != count_token_type(token, RPAREN))
		return (false);
	if (open == 0)
		return (true);
	depth = 0;
	while (token)
	{
		if (token->type == LPAREN && token->next->type == RPAREN)
			return (false);
		if (token->type == LPAREN)
			depth++;
		else if (token->type == RPAREN)
			depth--;
		if (depth < 0)
			return (false);
		token = token->next;
	}
	return (true);
}

bool	validate_redirects(t_token *token)
{
	while (token)
	{
		if (is_redirect(token->type))
		{
			if (!token->next)
				return (false);
			if (token->next->type != TEXT)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	validate_operators(t_token *token)
{
	while (token)
	{
		if (is_operator(token->type))
		{
			if (!token->prev || !token->next)
				return (false);
			if (is_operator(token->prev->type) || \
				is_operator(token->next->type))
				return (false);
			if (token->prev->type == LPAREN || \
				token->next->type == RPAREN)
				return (false);
			if (is_redirect(token->prev->type) || \
				is_redirect(token->next->type))
				return (false);
		}
		token = token->next;
	}
	return (true);
}

// TODO: Correct Error Message
int	tokens_validate(t_token *token)
{
	int	*error_code;

	error_code = get_error_code();
	if (!validate_subshells(token))
		*error_code = print_error("Syntax Error: invalid subshell usage", 2);
	else if (!validate_redirects(token))
		*error_code = print_error("Syntax Error: invalid redirect usage", 2);
	else if (!validate_operators(token))
		*error_code = print_error("Syntax Error: invalid operator usage", 2);
	return (*error_code);
}

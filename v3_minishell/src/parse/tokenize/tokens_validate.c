#include "../../../inc/minishell.h"

bool	is_operator(e_tree_node_type type)
{
	if (type == AND_IF)
		return (true);
	else if (type == OR_IF)
		return (true);
	else if (type == PIPE)
		return (true);
	return (false);
}

int	count_token_type(t_token *token, e_tree_node_type type)
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
		if (is_redirect(token->type) && (!token->prev || !token->next || \
				token->prev->type != TEXT || token->next->type != TEXT))
			return (false);
		token = token->next;
	}
	return (true);	
}

bool	validate_operators(t_token *token)
{
	while (token)
	{
		if (is_operator(token->type) && (!token->prev || !token->next || \
				is_operator(token->prev->type) || is_operator(token->next->type)))
			return (false);
		token = token->next;
	}
	return (true);	
}

void	tokens_validate(t_token *token)
{
	if (!validate_subshells(token))
		ft_error("invalid subshell usage in token list", __FILE__, __LINE__, 998);
	if (!validate_redirects(token))
		ft_error("invalid redirect usage in token list", __FILE__, __LINE__, 998);
	if (!validate_operators(token))
		ft_error("invalid operator usage in token list", __FILE__, __LINE__, 998);
}

// int	tokens_validate(t_token *token)
// {
// 	if (!validate_subshells(token))
// 		return (1);
// 	if (!validate_redirects(token))
// 		return (2);
// 	if (!validate_operators(token))
// 		return (3);
// 	return (0);
// }

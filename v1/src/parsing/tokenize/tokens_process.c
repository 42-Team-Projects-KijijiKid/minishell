#include "../../../inc/minishell.h"

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
static e_tree_node_type	get_token_type(t_token *token)
{
	int	len;

	len = ft_strlen(*token->args);
	char *a = *token->args;
	if (ft_strncmp(token->args[0], "|", len) == 0)
		return (PIPE);
	else if (ft_strncmp(token->args[0], "(", len) == 0)
		return (LPAREN);
	else if (ft_strncmp(token->args[0], ")", len) == 0)
		return (RPAREN);
	else if (ft_strncmp(token->args[0], "&&", len) == 0)
		return (AND_IF);
	else if (ft_strncmp(token->args[0], "||", len) == 0)
		return (OR_IF);
	else if (ft_strncmp(token->args[0], "<", len) == 0)
		return (LESS);
	else if (ft_strncmp(token->args[0], ">", len) == 0)
		return (GREAT);
	else if (ft_strncmp(token->args[0], ">>", len) == 0)
		return (DGREAT);
	else if (ft_strncmp(token->args[0], "<<", len) == 0)
		return (DLESS);
	else
		return (TEXT);
}

/// @brief Turns the command linked list
/// into the nodes for the parsing
/// also in a linked list like way
/// (always assigned on left)
/// Token type is already assigned here.
/// @param head_token 
/// @return 
t_token	*tokens_process(t_token *head_token)
{
	t_token	*current_token;

	current_token = head_token;
	while (current_token)
	{
		current_token->type = get_token_type(current_token);
		current_token = current_token->next;
		if (current_token->next == head_token) // circular check; necessary?
			return (head_token);
	}
	return (head_token);
}

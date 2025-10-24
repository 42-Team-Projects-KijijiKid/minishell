#include "parsing.h"

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
static t_token_enum	evaluate_token_type(t_tmp_cmd_token *cmd)
{
	if (ft_strncmp(cmd->value, "|", ft_strlen(cmd->value)) == 0)
		return (T_PIPE);
	else if (ft_strncmp(cmd->value, "&&", ft_strlen(cmd->value)) == 0)
		return (T_AND);
	else if (ft_strncmp(cmd->value, "||", ft_strlen(cmd->value)) == 0)
		return (T_OR);
	else if (ft_strncmp(cmd->value, "<", ft_strlen(cmd->value)) == 0)
		return (T_IN_RDR);
	else if (ft_strncmp(cmd->value, ">", ft_strlen(cmd->value)) == 0)
		return (T_OUT_RDR);
	else if (ft_strncmp(cmd->value, ">>", ft_strlen(cmd->value)) == 0)
		return (T_APPEND);
	else if (ft_strncmp(cmd->value, "<<", ft_strlen(cmd->value)) == 0)
		return (T_HEREDOC);
	else
		return (T_TEXT);
}

/// @brief Turns the command linked list
/// into the nodes for the parsing
/// also in a linked list like way
/// (always assigned on left)
/// Redirection list is handled elsewhere
/// @param cmd_head 
/// @return 
t_token	*create_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*head;
	t_token *token;
	t_token *prev;

	prev = NULL;
	while (cmd_head)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return NULL;
		token->type = evaluate_token_type(cmd_head);
		token->value = cmd_head->value;
		token->right = NULL;
		if (cmd_head->args_2d)
			token->args_2d = cmd_head->args_2d;
		if (prev)
			prev->left = token;
		else
			head = token;
		token->back = prev;	
		prev = token;
		cmd_head = cmd_head->prev;
	}
	return (head);
}

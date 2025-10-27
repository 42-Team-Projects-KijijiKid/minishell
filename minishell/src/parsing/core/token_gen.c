#include "parsing.h"

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
static t_token_enum	evaluate_token_type(t_tmp_cmd_token *cmd)
{
	if (ft_strncmp(cmd->args_2d[0], "|", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_PIPE);
	else if (ft_strncmp(cmd->args_2d[0], "&&", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_AND);
	else if (ft_strncmp(cmd->args_2d[0], "||", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_OR);
	else if (ft_strncmp(cmd->args_2d[0], "<", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_IN_RDR);
	else if (ft_strncmp(cmd->args_2d[0], ">", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_OUT_RDR);
	else if (ft_strncmp(cmd->args_2d[0], ">>", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_APPEND);
	else if (ft_strncmp(cmd->args_2d[0], "<<", ft_strlen(cmd->args_2d[0])) == 0)
		return (T_HEREDOC);
	else
		return (T_TEXT);
}

/// @brief Nulls every value of the token.
/// Safety wise.
/// @param token 
static void	null_values(t_token *token)
{
	token->args_2d = NULL;
	token->back = NULL;
	token->left = NULL;
	token->right =NULL;
	token->redir_meta.head = NULL;
	token->redir_meta.tail = NULL;
	token->redir_meta.size = 0;
}

/// @brief Turns the command linked list
/// into the nodes for the parsing
/// also in a linked list like way
/// (always assigned on left)
/// Token type is already assigned here
/// @param cmd_head 
/// @return 
t_token	*create_tokens(t_tmp_cmd_token *cmd_head)
{
	t_token	*head;
	t_token *token;
	t_token *prev;
	t_meta	*meta;

	meta = get_meta();
	prev = NULL;
	while (cmd_head)
	{
		token = ft_malloc(sizeof(t_token), LAYER_2);
		null_values(token);
		token->type = evaluate_token_type(cmd_head);
		token->args_2d = cmd_head->args_2d;
		if (prev)
			prev->left = token;
		else
			head = token;
		token->back = prev;	
		prev = token;
		cmd_head = cmd_head->prev;
	}
	token->left = NULL;
	return (head);
}

#include "parsing.h"

static bool	is_redir_type(t_token_enum type)
{
	if (type == T_PIPE)
		return (true);
	else if (type == T_APPEND)
		return (true);
	else if (type == T_HEREDOC)
		return (true);
	else if (type == T_OUT_RDR)
		return (true);
	else if (type == T_IN_RDR)
		return (true);
	return (false);
}

/// @brief Creates the redirection nodes for 
/// pipes or similar and opens heredocs
void	set_redirections(t_token *head_token)
{
	t_redir	*redir_node;

	while (head_token)
	{
		if (is_redir_type(head_token->type))
		{
			if (head_token->type == T_PIPE)
				handle_pipe(head_token);
			else if (head_token->type == T_APPEND)
				handle_append(head_token);
			else if (head_token->type == T_HEREDOC)
				handle_heredoc(head_token);
			else if (head_token->type == T_OUT_RDR)
				handle_io_redir(head_token);
			else if (head_token->type == T_IN_RDR)
				handle_io_redir(head_token);
		}
		head_token= head_token->left;
	}
}

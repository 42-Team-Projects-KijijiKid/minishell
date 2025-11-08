#include "parsing.h"

/// @brief Standardizes the inital values
/// of the t_redir nodes
void	set_node_val(t_redir *node)
{
	node->fd = -1;
	node->next = NULL;
	node->path = NULL;
}

static bool	is_redir_type(t_token_enum type)
{
	if (type == PIPE)
		return (true);
	else if (type == DGREAT)
		return (true);
	else if (type == DLESS)
		return (true);
	else if (type == GREAT)
		return (true);
	else if (type == LESS)
		return (true);
	return (false);
}

/// @brief Creates the redirection nodes for 
/// pipes or similar and opens heredocs
void	set_redirections(t_token *head_token)
{
	printf("set_redirection not implemented\n");
	return ;
	while (head_token)
	{
		if (is_redir_type(head_token->type))
		{
			if (head_token->type == DGREAT)
				handle_append(head_token);
			else if (head_token->type == DLESS)
				handle_heredoc(head_token);
			else if (head_token->type == GREAT)
				head_token = handle_io_redir(head_token);
			else if (head_token->type == LESS)
				head_token = handle_io_redir(head_token);
		}
		head_token= head_token->left;
	}
}

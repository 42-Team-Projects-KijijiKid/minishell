#include "parsing.h"

/// @brief This function creates redirection nodes
/// and assign them to the given node
/// The redir are stored in Layer2 of the gc
/// @param token Token that the redir affect
/// @param redir_type Redirection type
/// @param fd the file desriptor
void	assign_redir_node_values(t_token *token, t_redir_type redir_type, int fd)
{
	t_redir	*redir_node;

	redir_node = ft_malloc(sizeof(t_redir), LAYER_2);
	set_node_val(redir_node);
	if (!token->redir_meta.head)
	{
		redir_node->fd = fd;
		redir_node->type = redir_type;
		token->redir_meta.head = redir_node;
		token->redir_meta.tail = redir_node;
	}
	else if (token->redir_meta.size <= 2)
	{
		redir_node->fd = fd;
		redir_node->type = redir_type;
		token->redir_meta.head->next = redir_node;
		token->redir_meta.tail = redir_node;
	}
	else
		ft_error("More than two redir for one command:", __FILE__, __LINE__, 38);
	token->redir_meta.size++;
}

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
				head_token = handle_io_redir(head_token);
			else if (head_token->type == T_IN_RDR)
				head_token = handle_io_redir(head_token);
		}
		head_token= head_token->left;
	}
}

#include "../../../inc/minishell.h"

/// @brief Standardizes the inital values
/// of the t_redirect_node nodes
void	set_node_val(t_redirect_node *node)
{
	node->fd = -1;
	node->next = NULL;
	node->path = NULL;
}

static bool	is_redirect(e_tree_node_type type)
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
void	prep_redirections(t_tree_node *head_node)
{
	printf("prep_redirections not implemented\n");
	return ;
	while (head_node)
	{
		if (is_redirect(head_node->type))
		{
			if (head_node->type == DGREAT)
				handle_append(head_node);
			else if (head_node->type == DLESS)
				handle_heredoc(head_node);
			else if (head_node->type == GREAT)
				head_node = handle_io_redir(head_node);
			else if (head_node->type == LESS)
				head_node = handle_io_redir(head_node);
		}
		head_node = head_node->left;
	}
}

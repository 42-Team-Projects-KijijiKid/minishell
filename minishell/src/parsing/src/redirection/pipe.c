#include "parsing.h"

static void	assign_redir_node_values(t_token *token, t_redir_type redir_type, int fd)
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

static void	write_end(t_token *token, int write_fd)
{
	assign_redir_node_values(token, OUT_FD, write_fd);
}

static void	read_end(t_token *token, int read_fd)
{
	assign_redir_node_values(token, IN_FD, read_fd);
}

void	handle_pipe(t_token *token)
{
	int	fd[2];

	pipe(fd);
	if (!token->back || !token->left)
		ft_error("Pipe Error:",__FILE__, __LINE__, 122);
	write_end(token->back, fd[1]);
	read_end(token->left, fd[0]);
}

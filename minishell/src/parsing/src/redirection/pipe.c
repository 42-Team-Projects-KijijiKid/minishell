#include "parsing.h"

static void	write_end(t_token *token, int write_fd)
{
	t_redir	*redir_node;

	redir_node = ft_malloc(sizeof(t_redir), LAYER_2);
	if (!token->redir_meta.head)
	{
		redir_node->type = OUT_FD;
		redir_node->fd = write_fd;
		redir_node->path = NULL;
		redir_node->next =NULL;
	}
	else
	{
		redir_node->type = OUT_FD;
		redir_node->fd = write_fd;
		redir_node->path = NULL;
		redir_node->next =NULL;
		token->redir_meta.head->next = redir_node;
		token->redir_meta.tail = redir_node;
	}
}

static void	read_end(t_token *token, int read_fd)
{
	t_redir	*redir_node;

	redir_node = ft_malloc(sizeof(t_redir), LAYER_2);
	if (!token->redir_meta.head)
	{
		redir_node->type = OUT_FD;
		redir_node->fd = read_fd;
		redir_node->path = NULL;
		redir_node->next =NULL;
	}
	else
	{
		redir_node->type = OUT_FD;
		redir_node->fd = read_fd;
		redir_node->path = NULL;
		redir_node->next =NULL;
		token->redir_meta.head->next = redir_node;
		token->redir_meta.tail = redir_node;
	}
	token->redir_meta.size++;
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

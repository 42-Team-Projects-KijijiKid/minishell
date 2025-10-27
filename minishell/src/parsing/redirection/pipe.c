#include "parsing.h"

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

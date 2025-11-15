#include "../../inc/minishell.h"

static void	execute_pipe_right(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdin;
	int	status;
	
	close(write_fd);
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		ft_error("Dup2 failed", __FILE__, __LINE__, 913);
	}
	close(read_fd);
	execute_node(node->right);
	close(STDIN_FILENO);
	// if (!WIFEXITED(status))
	// 	ft_error("Unexpected error in pipe execution right", __FILE__, __LINE__, 1);
}

static void	execute_pipe_left(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdout;

	if (dup2(write_fd, STDOUT_FILENO) == -1)
		exit(127);
	close(write_fd);
	execute_node(node->left);
	close(STDOUT_FILENO);
}

void	execute_pipe(t_tree_node *node)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		ft_error("Pipe creation failed", __FILE__, __LINE__, 910);
	if (node->left->type != PIPE)
	{
		execute_pipe_left(node, pipe_fds[0], pipe_fds[1]);
		execute_pipe_right(node, pipe_fds[0], pipe_fds[1]);
	}
	else
	{

	}
}

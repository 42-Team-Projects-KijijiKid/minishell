#include "../../inc/minishell.h"

static void	execute_pipe_left(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdout;

	if (node && node->left->type == PIPE)
		execute_pipe(node->left);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit(127);
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		exit(127);
	execute_node(node->left);
	close(write_fd);
}

static void	execute_pipe_right(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdin;
	int	status;
	
	close(write_fd);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		close(read_fd);
		ft_error("Dup failed", __FILE__, __LINE__, 912);
	}
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		ft_error("Dup2 failed", __FILE__, __LINE__, 913);
	}
	execute_node(node->right);
	close(read_fd);
	// if (!WIFEXITED(status))
	// 	ft_error("Unexpected error in pipe execution right", __FILE__, __LINE__, 1);
}

void	execute_pipe(t_tree_node *node)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		ft_error("Pipe creation failed", __FILE__, __LINE__, 910);
	execute_pipe_left(node, pipe_fds[0], pipe_fds[1]);
	execute_pipe_right(node, pipe_fds[0], pipe_fds[1]);
}

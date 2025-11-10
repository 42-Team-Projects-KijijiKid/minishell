#include "../../inc/minishell.h"

static void	execute_pipe_left(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdout;
	int	status;

	close(read_fd);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		_exit(1);
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		_exit(1);
	status = execute_node(node->left);
	close(write_fd);
	_exit(status);
}

static int	execute_pipe_right(t_tree_node *node, int read_fd, int write_fd, pid_t child_pid)
{
	int	saved_stdin;
	int	status;
	
	close(write_fd);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		close(read_fd);
		return (ft_error("Dup failed", __FILE__, __LINE__, 912), 912);
	}
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		return (ft_error("Dup2 failed", __FILE__, __LINE__, 913), 913);
	}
	waitpid(child_pid, &status, 0);
	status = execute_node(node->right);
	close(read_fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (ft_error("Unexpected error in pipe execution right", __FILE__, __LINE__, 1), 0);
}

int	execute_pipe(t_tree_node *node)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (!node || node->type != PIPE)
		return (ft_error("Invalid node for pipe execution", __FILE__, __LINE__, 99), 99);
	if (pipe(pipe_fds) == -1)
		return (ft_error("Pipe creation failed", __FILE__, __LINE__, 910), 910);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	}
	if (pid == 0)
	{
		execute_pipe_left(node, pipe_fds[0], pipe_fds[1]);
	}
	else
	{
		return (execute_pipe_right(node, pipe_fds[0], pipe_fds[1], pid));
	}
	return (ft_error("Unexpected error in execute_pipe", __FILE__, __LINE__, 1), 0);
}

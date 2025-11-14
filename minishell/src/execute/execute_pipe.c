#include "../../inc/minishell.h"

static void	execute_pipe_left(t_tree_node *node, int read_fd, int write_fd)
{
	int	saved_stdout;

	close(read_fd);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit(127);
	if (dup2(write_fd, STDOUT_FILENO) == -1)
		exit(127);
	execute_node(node->left);
	close(write_fd);
	exit(127);
}

static void	execute_pipe_right(t_tree_node *node, int read_fd, int write_fd, pid_t child_pid)
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
	waitpid(child_pid, &status, 0); // Question: waitpid overwrites the status variable with the exit status of the child process?
	execute_node(node->right);
	close(read_fd);
	if (!WIFEXITED(status))
		ft_error("Unexpected error in pipe execution right", __FILE__, __LINE__, 1);
}

void	execute_pipe(t_tree_node *node)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		ft_error("Pipe creation failed", __FILE__, __LINE__, 910);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	}
	if (pid == 0)
		execute_pipe_left(node, pipe_fds[0], pipe_fds[1]);
	else
		execute_pipe_right(node, pipe_fds[0], pipe_fds[1], pid);
	// ft_error("Unexpected error in execute_pipe", __FILE__, __LINE__, 993);
}

#include "../../inc/minishell.h"

static void	execute_last_node(t_tree_node *node, int in_fd)
{
	int	pid;

	pid = ft_fork();
	if (pid < 0)
		ft_error("fork failed", __FILE__, __LINE__, 131);
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				close(in_fd);
				ft_error("dup2 failed", __FILE__, __LINE__, 131);
			}
			close(in_fd);
		}
		execute_node(node);
		garbage_free_all();
		exit (minishell_get()->last_exit_status);
	}
	minishell_get()->pipe_pid = pid;
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

static void	fd_error(int in, int r, int w, int code)
{
	if (in >= 0)
		close(in);
	if (r >= 0)
		close(r);
	if (w >= 0)
		close(w);
	ft_error("Dup2 failed", __FILE__, __LINE__, code);
}

static void	execute_left_tree(t_tree_node *node,
	int in_fd, int read_fd, int write_fd)
{
	int	pid;

	pid = ft_fork();
	if (pid < 0)
		ft_error("fork failed", __FILE__, __LINE__, 131);
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
				fd_error(in_fd, read_fd, write_fd, 131);
			close(in_fd);
		}
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			fd_error(-1, read_fd, write_fd, 131);
		close(read_fd);
		close(write_fd);
		execute_node(node->left);
		garbage_free_all();
		exit(EXIT_SUCCESS);
	}
}

static void	exec_pipe_recursive(t_tree_node *node, int in_fd)
{
	int		pipe_fds[2];

	if (node->type != PIPE)
	{
		execute_last_node(node, in_fd);
		return ;
	}
	if (pipe(pipe_fds) == -1)
		ft_error("Pipe creation failed", __FILE__, __LINE__, 12);
	execute_left_tree(node, in_fd, pipe_fds[0], pipe_fds[1]);
	close(pipe_fds[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	exec_pipe_recursive(node->right, pipe_fds[0]);
}

void	execute_pipe(t_tree_node *node)
{
	int			status;
	t_minishell	*shell;

	shell = minishell_get();
	exec_pipe_recursive(node, STDIN_FILENO);
	if (waitpid(shell->pipe_pid, &status, 0) == -1)
		shell->last_exit_status = 127;
	else if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
	wait(NULL);
	default_filedescripor();
}

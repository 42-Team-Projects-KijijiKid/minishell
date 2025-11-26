#include "../../inc/minishell.h"

static void	execute_last_node(t_tree_node *node, int in_fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork failed", __FILE__, __LINE__, 911);
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				close(in_fd);
				ft_error("dup2 failed", __FILE__, __LINE__, 913);
			}
			close(in_fd);
		}
		execute_node(node);
		exit(EXIT_SUCCESS);
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

static void	execute_left_tree(t_tree_node *node, \
	int in_fd, int read_fd, int write_fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork failed", __FILE__, __LINE__, 911);
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				close(in_fd);
				close(read_fd);
				close(write_fd);
				ft_error("Dup2 failed", __FILE__, __LINE__, 913);
			}
			close(in_fd);
		}
		if (dup2(write_fd, STDOUT_FILENO) == -1)
		{
			close(read_fd);
			close(write_fd);
			ft_error("Dup2 failed", __FILE__, __LINE__, 913);
		}
		close(read_fd);
		close(write_fd);
		execute_node(node->left);
		exit(EXIT_SUCCESS);
	}
}

static void	exec_pipe_recursive(t_tree_node *node, int in_fd)
{
	int		pipe_fds[2];
	pid_t	pid;

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
	while (wait(&status) > 0)
		continue ;
	shell->last_exit_status = status;
	default_filedescripor();
}

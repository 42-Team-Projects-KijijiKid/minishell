#include "../../../inc/minishell.h"

int execute_rdr_in(t_tree_node *node)
{
	int	fd;
	int	saved_stdin;
	int	status;

	if (!node || node->type != LESS)
		return (ft_error("Node is NULL or has incorrect type", __FILE__, __LINE__, 950), 950);
	fd = get_redirect_fd(node->left);
	if (fd == -1)
		return (ft_error("Failed to open file for input redirection", __FILE__, __LINE__, 951), 951);
	saved_stdin = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ft_error("Failed to duplicate file descriptor for input redirection", 
			__FILE__, __LINE__, 952), 952);
	}
	close(fd);
	status = execute_node(node->right);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	return (status);
}

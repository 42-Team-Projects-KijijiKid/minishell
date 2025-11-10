#include "../../../inc/minishell.h"

int execute_rdr_append(t_token *node)
{
	int	fd;
	char *filename;
	int	saved_stdout;
	int	status;

	if (!node || node->type != DGREAT)
		return (ft_error("Node is NULL or has incorrect type", __FILE__, __LINE__, 950), 950);
	filename = get_redirect_filename(node->left);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_error("Failed to open file for append redirection", __FILE__, __LINE__, 951), 951);
	saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_error("Failed to duplicate file descriptor for append redirection", \
			__FILE__, __LINE__, 952), 952);
	}
	close(fd);
	status = execute_node(node->right);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (status);
}

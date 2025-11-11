#include "../../../inc/minishell.h"

char	*get_redirect_filename(t_tree_node *node)
{
	if (!node)
		return (ft_error("Node is NULL", __FILE__, __LINE__, 0), NULL);
	if (!(node->args) || ft_strlen(node->args[0]) == 0)
		return (ft_error("Node arg is NULL or empty", __FILE__, __LINE__, 0), NULL);
	if (node->args[1])
		return (ft_error("Multiple filenames in redirection", __FILE__, __LINE__, 0), NULL);
	return (node->args[0]);
}

int get_redirect_fd(t_tree_node *node)
{
	char *filename;
	int fd;

	filename = get_redirect_filename(node);
	fd = open(filename, O_RDONLY);
	return (fd);
}

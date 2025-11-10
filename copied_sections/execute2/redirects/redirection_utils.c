#include "../../../inc/minishell.h"

char	*get_redirect_filename(t_token *node)
{
	if (!node)
		return (ft_error("Node is NULL", __FILE__, __LINE__, 0), NULL);
	if (!(node->arg) || ft_strlen(node->arg) == 0)
		return (ft_error("Node arg is NULL or empty", __FILE__, __LINE__, 0), NULL);
	if (node->arg[1])
		return (ft_error("Multiple filenames in redirection", __FILE__, __LINE__, 0), NULL);
	return (node->arg[0]);
}

int get_redirect_fd(t_token *node)
{
	char *filename;
	int fd;

	filename = get_redirect_filename(node);
	fd = open(filename, O_RDONLY);
	return (fd);
}

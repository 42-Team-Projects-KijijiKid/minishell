#include "execution.h"

void	execution_process(t_token *token)
{
	int		id;
	char	*path;
	char	**paths_2d;

	paths_2d = extract_path();
	char *tmp = *paths_2d;
	path = access_path(*token->args_2d, paths_2d);
	if (!path)
		write(2, "error\n", 6);
	id = fork();
	if (id == 0)
		execve(path, token->args_2d, NULL);
}

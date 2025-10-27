#include "execution.h"

void	execution_process(t_token *token)
{
	int 	id;
	char	**env;
	char	*path;
	t_meta	*meta;

	meta = get_meta();
	env = extract_path(meta->envp);
	path = access_path(*token->args_2d, env);
	id = fork();
	if (id == 0)
	{
		execve(path, token->args_2d, NULL);
	}
}

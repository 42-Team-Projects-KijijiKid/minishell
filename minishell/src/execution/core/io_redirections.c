#include "execution.h"

/// @brief run command in a child process,
/// parent waits for
/// closes out file descriptor in partent
/// @param token command token
/// @param in_fd file descriptor for infile
/// @param out_fd file descriptor for outfile
void	run_cmd(t_token *token, int in_fd, int out_fd)
{
	int		pid;
	t_meta	*meta;

	pid = ft_fork();
	meta = get_meta();
	if (pid == 0)
	{
		char	*path;
		char	**paths_2d;

		paths_2d = extract_path();
		if (2 < in_fd)
			dup2(in_fd, STDIN_FILENO);
		if (2 < out_fd)
			dup2(out_fd, STDOUT_FILENO);
		path = access_path(*token->args_2d, paths_2d);
		execve(path, token->args_2d, meta->envp);
	}
	else
	{
		wait(NULL);
		if (2 < out_fd)
			close(out_fd);
	}

}


void	out_redir(t_token *token)
{
	printf("%d\n", token->left->redir_meta.head->fd);
	run_cmd(token->left, 0, token->left->redir_meta.head->fd);
}

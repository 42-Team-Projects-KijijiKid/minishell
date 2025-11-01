#include "execution.h"

/// @brief run command in a child process,
/// parent waits for
/// closes out file descriptor in partent
/// @param token command token
/// @param in_fd file descriptor for infile
/// @param out_fd file descriptor for outfile
void	run_cmd(t_token *token, t_redir_type redir_type, int fd)
{
	char	*path;
	char	**paths_2d;
	int		pid;
	t_meta	*meta;

	pid = ft_fork();
	meta = get_meta();
	if (pid == 0)
	{
		// paths_2d = extract_path();
		path = access_path(*token->args_2d, paths_2d);
		if (redir_type == IN_FD)
			dup2(fd, STDIN_FILENO);
		if (redir_type == OUT_FD)
			dup2(fd, STDOUT_FILENO);
		execve(path, token->args_2d, NULL);
	}
	else
	{
		wait(NULL);
		if (redir_type != STD)
			close(fd);
	}
}

void	out_redir(t_token *token)
{
	run_cmd(token->left, token->left->redir_meta.head->type, token->left->redir_meta.head->fd);
}

void	in_redir(t_token *token)
{
	run_cmd(token->left, token->left->redir_meta.head->type, token->left->redir_meta.head->fd);
}

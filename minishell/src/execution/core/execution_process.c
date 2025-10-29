#include "execution.h"

// void	exec_pipe(t_token *token, bool write)
// {
// 	if (!token->redir_meta.head)
// 		ft_error("Redirection failed:", __FILE__, __LINE__, 27);
// 	else if (token->redir_meta.head->type == T_PIPE && write)
// 	{
// 		dup2(STDOUT_FILENO, token->redir_meta.head->fd);
// 	}
// 	else if (token->redir_meta.head->type == T_PIPE && !write)
// 		dup2(STDIN_FILENO, token->redir_meta.head->fd);
// }

// void	run_pipe(t_token *token)
// {
// 	char	*path;
// 	char	**paths_2d;

// 	if (ft_fork())
// 	{
// 		exec_pipe(token->left, true);
// 		paths_2d = extract_path();
// 		path = access_path(*token->left->args_2d, paths_2d);
// 		execve(path, token->args_2d, NULL);
// 	}
// 	if (ft_fork())
// 	{
// 		exec_pipe(token->right, false);
// 		paths_2d = extract_path();
// 		path = access_path(*token->right->args_2d, paths_2d);
// 		execve(path, token->args_2d, NULL);
// 	}
// }

void	execution_process(t_token *token)
{
	if (T_TEXT == token->type)
		run_cmd(token, STD, 1);
	else if (T_OUT_RDR == token->type)
		out_redir(token);
	else if (T_IN_RDR == token->type)
		in_redir(token);
}

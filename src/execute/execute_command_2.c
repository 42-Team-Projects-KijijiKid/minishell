#include "minishell.h"

static char	*resolve_bin_path(char *cmd, char **split_path)
{
	if (split_path)
		return (get_bin_path_of_command(cmd, split_path));
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

static void	execute_executable(t_tree_node *node)
{
	char	**envp;
	char	**split_path;
	char	*bin_path;

	envp = env_list_to_2d();
	split_path = get_path_array(envp);
	bin_path = resolve_bin_path(*node->args, split_path);
	if (!bin_path)
	{
		if (access(*node->args, X_OK) == 0)
			bin_path = *node->args;
		else
		{
			ft_fprintf(2, "%s: command not found\n", *node->args);
			exit(127);
		}
	}
	close_default_filedescriptor();
	execve(bin_path, node->args, envp);
	exit(127);
}

void	handle_child_exit(t_minishell *sh, t_tree_node *n)
{
	int	pid;
	int	st;

	pid = ft_fork();
	if (pid == 0)
		execute_executable(n);
	if (waitpid(pid, &st, 0) == -1)
		sh->last_exit_status = 127;
	else if (WIFEXITED(st))
		sh->last_exit_status = WEXITSTATUS(st);
	else if (WIFSIGNALED(st))
		sh->last_exit_status = 128 + WTERMSIG(st);
	else
		sh->last_exit_status = 1;
	sig_init();
}


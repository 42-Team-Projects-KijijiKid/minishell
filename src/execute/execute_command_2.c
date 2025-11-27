#include "minishell.h"

static int	is_file(const char *cmd)
{
	DIR	*directory;

	if (!cmd)
		return (0);
	directory = opendir(cmd);
	if (directory != NULL)
	{
		closedir(directory);
		ft_fprintf(2, "%s: Is a directory\n", cmd);
		exit (126);
	}
	return (0);
}


static char	*resolve_bin_path(char *cmd, char **split_path)
{
	char	*bin_path;

	if (split_path)
	{
		bin_path = get_bin_path_of_command(cmd, split_path);
		if (bin_path)
			return (bin_path);
	}
	if (access(cmd, X_OK) == 0
		&& !is_file(cmd))
		return (cmd);
	return (NULL);
}

static void	execute_executable(t_tree_node *node)
{
	char	**envp;
	char	**split_path;
	char	*bin_path;

	if (!node->args)
		exit (0);
	envp = env_list_to_2d();
	split_path = get_path_array(envp);
	bin_path = resolve_bin_path(*node->args, split_path);
	if (!bin_path)
	{
		if (access(*node->args, X_OK) == 0
			&& !is_file(*node->args))
			bin_path = *node->args;
		else
		{
			ft_fprintf(2, "%s: command not found\n", *node->args);
			exit(127);
		}
	}
	close_default_filedescriptor();
	execve(bin_path, node->args, envp);
	is_file(*node->args);
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


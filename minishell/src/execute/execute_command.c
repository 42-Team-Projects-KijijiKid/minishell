#include "../../inc/minishell.h"

static int	execute_builtin(t_tree_node *node)
{
	if (ft_strncmp(node->args[0], "cd", ft_strlen(*node->args)) == 0)
		return (builtin_cd(node->args));
	else if (ft_strncmp(node->args[0], "echo", ft_strlen(*node->args)) == 0)
		return (builtin_echo(node->args));
	else if (ft_strncmp(node->args[0], "exit", ft_strlen(*node->args)) == 0)
		return (builtin_exit(node->args));
	else if (ft_strncmp(node->args[0], "export", ft_strlen(*node->args)) == 0)
		return (builtin_export(node->args));
	else if (ft_strncmp(node->args[0], "unset", ft_strlen(*node->args)) == 0)
		return (builtin_unset(node->args));
	else if (ft_strncmp(node->args[0], "pwd", ft_strlen(*node->args)) == 0)
		return (builtin_pwd(node->args));
	else if (ft_strncmp(node->args[0], "env", ft_strlen(*node->args)) == 0)
		return (builtin_env(node->args));
	return (-1); 
}

static int	execute_executable(t_tree_node *node)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	if (pid == 0)
	{
		execve(node->args[0], node->args, NULL);
		ft_error("Execve failed", __FILE__, __LINE__, 127);
		_exit(127);
	}
	else
	{
		if (waitpid(pid, &wstatus, 0) == -1)
			return (ft_error("Waitpid failed", __FILE__, __LINE__, 914), 914);
		if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		return (ft_error("Unexpected error in executable execution", __FILE__, __LINE__, 1), 0);
	}
}

int execute_command(t_tree_node *node)
{
	int status;

	if (!node || node->type != TEXT || node->args == NULL || node->args[0] == NULL)
		return (ft_error("Invalid node for command execution", __FILE__, __LINE__, 98), 98);
	status = execute_builtin(node);
	if (status == 0)
		return (0);
	if (status == -1)
		return (execute_executable(node));
	return (status);
}

#include "../../inc/minishell.h"

int	execute_builtin(t_token *node)
{
	if (ft_strcmp(node->arg, "cd") == 0)
		return (builtin_cd());
	else if (ft_strcmp(node->arg, "echo") == 0)
		return (builtin_echo());
	else if (ft_strcmp(node->arg, "exit") == 0)
		return (builtin_exit());
	else if (ft_strcmp(node->arg, "export") == 0)
		return (builtin_export());
	else if (ft_strcmp(node->arg, "unset") == 0)
		return (builtin_unset());
	else if (ft_strcmp(node->arg, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(node->arg, "env") == 0)
		return (builtin_env());
	return (-1); 
}

int	execute_executable(t_token *node)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (ft_error("Fork failed", __FILE__, __LINE__, 92), 92);
	if (pid == 0)
	{
		execve(node->arg, NULL, NULL);
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

int execute_command(t_token *node)
{
	int status;

	if (!node || node->type != TEXT || node->arg == NULL)
		return (ft_error("Invalid node for command execution", __FILE__, __LINE__, 98), 98);
	status = execute_builtin(node);
	if (status == 0)
		return (0);
	if (status == -1)
		return (execute_executable(node));
	return (status);
}

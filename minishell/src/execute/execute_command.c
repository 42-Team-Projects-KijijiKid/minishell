	#include "../../inc/minishell.h"

/// @brief Checks if command node is a builting
/// and executes if so
/// @param node 
/// @return 0 if its a builtin
/// 1 if builtin is not found
static int	execute_builtin(t_tree_node *node)
{
	int			exit;
	t_minishell	*shell;

	shell = minishell_get();
	exit = 0;
	if (ft_strncmp(node->args[0], "cd", ft_strlen(*node->args)) == 0)
		exit = builtin_cd(node->args);
	else if (ft_strncmp(node->args[0], "echo", ft_strlen(*node->args)) == 0)
		exit = builtin_echo(node->args);
	else if (ft_strncmp(node->args[0], "exit", ft_strlen(*node->args)) == 0)
		exit = builtin_exit(node->args);
	else if (ft_strncmp(node->args[0], "export", ft_strlen(*node->args)) == 0)
		exit = builtin_export(node->args);
	else if (ft_strncmp(node->args[0], "unset", ft_strlen(*node->args)) == 0)
		exit = builtin_unset(node->args);
	else if (ft_strncmp(node->args[0], "pwd", ft_strlen(*node->args)) == 0)
		exit = builtin_pwd(node->args);
	else if (ft_strncmp(node->args[0], "env", ft_strlen(*node->args)) == 0)
		exit = builtin_env(node->args);
	else
		exit = 1;
	if (exit != 1) 
		shell->last_exit_status = exit;
	return (exit);
}

static void	execute_executable(t_tree_node *node)
{
	char	**envp;
	char	**split_path;
	char	*bin_path;

	envp = env_list_to_2d();
	split_path = get_path_array(envp);
	bin_path = get_bin_path_of_command(*node->args, split_path);
	if (!bin_path && split_path)
		execve(bin_path, node->args, envp);
	exit (120);
}

void	execute_redirects(t_tree_node *node)
{
	t_redirect_node	*redirect;

	redirect = node->redirect.head;
	while (redirect)
	{
		if (redirect->type == LESS)
			execute_rdr_in(redirect);
		else if (redirect->type == GREAT)
			execute_rdr_out(redirect);
		else if (redirect->type == DLESS)
			execute_rdr_heredoc(redirect);
		else if (redirect->type == DGREAT)
			execute_rdr_append(redirect);
		redirect = redirect->next;
	}
}

void execute_command(t_tree_node *node)
{
	int			status;
	t_minishell	*shell; 
	int			pid;
	int			wstatus;

	shell = minishell_get();
	if (node->args == NULL || *node->args == NULL)
		ft_error("Invalid args for command execution", __FILE__, __LINE__, 98);
	execute_redirects(node);
	if (execute_builtin(node) == 1)
	{
		pid = fork();
		if (pid == -1)
			ft_error("Fork failed", __FILE__, __LINE__, 92);
		if (pid == 0)
			execute_executable(node);
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			shell->last_exit_status = 0;
		else
			shell->last_exit_status = 1;
	}
}

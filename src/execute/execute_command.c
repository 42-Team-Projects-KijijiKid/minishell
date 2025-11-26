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
	int			len;

	shell = minishell_get();
	exit = -1;
	len = ft_strlen(*node->args);
	if (!ft_strncmp(node->args[0], "cd", len) && len == 2)
		exit = builtin_cd(node->args);
	else if (!ft_strncmp(node->args[0], "echo", len) && len == 4)
		exit = builtin_echo(node->args);
	else if (!ft_strncmp(node->args[0], "exit", len) && len == 4)
		builtin_exit(node->args);
	else if (!ft_strncmp(node->args[0], "export", len) && len == 6)
		exit = builtin_export(node->args);
	else if (!ft_strncmp(node->args[0], "unset", len) && len == 5)
		exit = builtin_unset(node->args);
	else if (!ft_strncmp(node->args[0], "pwd", len) && len == 3)
		exit = builtin_pwd(node->args);
	else if (!ft_strncmp(node->args[0], "env", len) && len == 3)
		exit = builtin_env(node->args);
	if (exit != -1)
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
	if (!split_path)
	{
		if (access(*node->args, X_OK) == 0)
			bin_path = *node->args;
		else
		{
			ft_fprintf(2, "%s: command not found\n", *node->args);
			exit (127);
		}
	}
	else
		bin_path = get_bin_path_of_command(*node->args, split_path);
	if (!bin_path)
	{
		if (access(*node->args, X_OK) == 0)
			bin_path = *node->args;
		else
		{
			ft_fprintf(2, "%s: command not found\n", *node->args);
			exit (127);
		}
	}
	close_default_filedescriptor();
	execve(bin_path, node->args, envp);
	exit (127);
}

static int	execute_redirects(t_tree_node *node)
{
	t_redirect_node	*redirect;
	t_minishell		*shell;
	int				exit_code;

	shell = minishell_get();
	redirect = node->redirect.head;
	exit_code = 0;
	while (redirect && exit_code == 0)
	{
		if (redirect->type == LESS)
			exit_code = execute_rdr_in(redirect);
		else if (redirect->type == GREAT)
			exit_code = execute_rdr_out(redirect);
		else if (redirect->type == DLESS)
			execute_rdr_heredoc(redirect);
		else if (redirect->type == DGREAT)
			exit_code = execute_rdr_append(redirect);
		redirect = redirect->next;
	}
	if (exit_code == 1)
		shell->last_exit_status = exit_code;
	return (exit_code);
}

void	execute_command(t_tree_node *node)
{
	t_minishell	*shell;
	int			pid;
	int			wstatus;

	expand(node);
	shell = minishell_get();
	if (node->args == NULL)
		ft_fprintf(2, INVALID_ARGS_EXECUTION, __FILE__);
	if (execute_redirects(node))
		return ;
	if (node->args[0] != NULL)
	{
		if (execute_builtin(node) == -1 && shell->herdoc)
		{
			pid = ft_fork();
			if (pid == 0)
				execute_executable(node);
			if (waitpid(pid, &wstatus, 0) == -1 || wstatus != 0)
				shell->last_exit_status = 127;
			else
				shell->last_exit_status = 0;
			sig_init();
		}
	}
	default_filedescripor();
}

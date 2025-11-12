#include "../../inc/minishell.h"

static void	execute_builtin(t_tree_node *node)
{
	if (ft_strcmp(node->args[0], "cd") == 0)
		builtin_cd(node->args);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		builtin_echo(node->args);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(node->args);
	else if (ft_strcmp(node->args[0], "export") == 0)
		builtin_export(node->args);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		builtin_unset(node->args);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd(node->args);
	else if (ft_strcmp(node->args[0], "env") == 0)
		builtin_env(node->args);
}

static void	execute_executable(t_tree_node *node)
{
	execve(node->args[0], node->args, NULL);
	ft_error("Execve failed", __FILE__, __LINE__, 927);
}

void	execute_redirects(t_tree_node node)
{
	t_redirect_node	redirect;

	redirect = node->redirect->head; // TODO: redirect meta unnecessary; delete
	while (redirect)
	{
		if (redirect->type == LESS)
			execute_rdr_in(redirect);
		else if (redirect->type == GREAT)
			execute_rdr_in(redirect);
		else if (redirect->type == DLESS)
			execute_rdr_in(redirect);
		else if (redirect->type == DGREAT)
			execute_rdr_in(redirect);
		redirect = redirect->next;
	}
}

void execute_command(t_tree_node *node)
{
	int status;

	if (node->args == NULL || node->args[0] == NULL)
		ft_error("Invalid args for command execution", __FILE__, __LINE__, 98);
	execute_redirects(node);
	execute_builtin(node);
	execute_executable(node);
}

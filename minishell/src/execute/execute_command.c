	#include "../../inc/minishell.h"

static void	execute_builtin(t_tree_node *node)
{
	if (ft_strncmp(node->args[0], "cd", ft_strlen(*node->args)) == 0)
		builtin_cd(node->args);
	else if (ft_strncmp(node->args[0], "echo", ft_strlen(*node->args)) == 0)
		builtin_echo(node->args);
	else if (ft_strncmp(node->args[0], "exit", ft_strlen(*node->args)) == 0)
		builtin_exit(node->args);
	else if (ft_strncmp(node->args[0], "export", ft_strlen(*node->args)) == 0)
		builtin_export(node->args);
	else if (ft_strncmp(node->args[0], "unset", ft_strlen(*node->args)) == 0)
		builtin_unset(node->args);
	else if (ft_strncmp(node->args[0], "pwd", ft_strlen(*node->args)) == 0)
		builtin_pwd(node->args);
	else if (ft_strncmp(node->args[0], "env", ft_strlen(*node->args)) == 0)
		builtin_env(node->args);
}

char	**extract_path(char **envp)
{
	char	**path_2d;

	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, ft_strlen("PATH=")) == 0)
		{
			path_2d = ft_split((*envp + 5), ':');
			return (path_2d);
		}
		envp++;
	}
	return (NULL);
}

char	*access_path(char *cmd, char **paths_2d)
{
	char	*path_cmd;
	char	*full_path;

	path_cmd = ft_strjoin("/", cmd);
	while (*paths_2d)
	{
		full_path = ft_strjoin(*paths_2d, path_cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_cmd);
			return (full_path);
		}
		free(full_path);
		paths_2d++;
	}
	free(path_cmd);
	return (NULL);
}

static void	execute_executable(t_tree_node *node)
{
	char	**envp;
	char	**split_path;
	char	*bin_path;

	envp = env_list_to_2d();
	split_path = extract_path(envp);
	bin_path = access_path(*node->args, split_path);
	execve(bin_path, node->args, envp);
	ft_error("Execve failed", __FILE__, __LINE__, 927);
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
	int status;

	if (node->args == NULL || *node->args == NULL)
		ft_error("Invalid args for command execution", __FILE__, __LINE__, 98);
	execute_redirects(node);
	execute_builtin(node);
	execute_executable(node);
}

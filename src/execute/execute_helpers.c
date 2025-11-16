#include "minishell.h"

char	**get_path_array(char **envp)
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

char	*get_bin_path_of_command(char *cmd, char **paths_2d)
{
	char	*path_cmd;
	char	*full_path;

	path_cmd = fti_strjoin("/", cmd);
	while (*paths_2d)
	{
		full_path = fti_strjoin(*paths_2d, path_cmd);
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

void	default_filedescripor(void)
{
	t_minishell	*shell;

	shell = minishell_get();
	dup2(shell->filedescriptor.std_in, STDIN_FILENO);
	dup2(shell->filedescriptor.std_out, STDOUT_FILENO);
	dup2(shell->filedescriptor.std_err, STDERR_FILENO);
}

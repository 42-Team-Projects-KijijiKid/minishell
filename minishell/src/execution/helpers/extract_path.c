#include "execution.h"

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
	char	*asd;

	path_cmd = ft_strjoin("/", cmd);
	while (*paths_2d)
	{
		asd = *paths_2d;
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

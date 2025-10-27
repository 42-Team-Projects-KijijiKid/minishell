#include "minishell.h"

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

int main(int ac, char **av, char **env)
{
	char	*cmd;
	t_meta	*meta;
	char	*path;

	meta = init_meta();
	// while (1)
	// {
	// 	cmd = readline("Minishell>> ");
	// 	printf("Command Print: %s\n", cmd);
	// 	parsing_process(cmd);
	// }
	cmd = "ps -ef | grep systemd | awk '{print $2}' | grep -v grep";
	printf("Command Print: %s\n", cmd);
	parsing_process(cmd);
	free_gc();
}

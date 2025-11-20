#include "../../../inc/minishell.h"

int builtin_echo(char **args)
{
	int i;
	int newline;

	i = 1;
	// if(args[i])
	// {
	// 	printf("%s", args[i]);
	// 	newline = 1;
	// 	i++;
	// }
	// while (args[i] && ft_strncmp(args[i], "-n", ft_strlen(args[i])) == 0) // New version required, that adds to garbage collector
	// {
	// 	newline = 0;
	// 	i++;
	// }
	while (args[i])
	{
		ft_fprintf(STDOUT_FILENO,"%s", args[i]);
		if (args[i + 1] 
			&& *args[i] != ' ')
			ft_fprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (newline)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (0);
}

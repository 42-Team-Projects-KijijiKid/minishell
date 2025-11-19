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
		printf("%s", args[i]);
		if (args[i + 1] 
			&& *args[i] != ' ')
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

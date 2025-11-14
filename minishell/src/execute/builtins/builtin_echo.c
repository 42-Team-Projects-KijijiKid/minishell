#include "../../../inc/minishell.h"

int builtin_echo(char **args)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0) // New version required, that adds to garbage collector
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		printf("%s", args[i]); // TODO: Question: check for printf errors?
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

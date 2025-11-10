#include "../../../inc/minishell.h"

int builtin_echo(char **args)
{
	int i;
	int newline;

	if (!args)
		return (1);
	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen(*args)) == 0) // New version required, that adds to garbage collector
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		if (printf("%s", args[i]) < 0)
			return (ft_error("printf failed", __FILE__, __LINE__, 933), 933);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
	{
		if (printf("\n") < 0)
			return (ft_error("printf failed", __FILE__, __LINE__, 933), 933);
	}
	return (0);
}

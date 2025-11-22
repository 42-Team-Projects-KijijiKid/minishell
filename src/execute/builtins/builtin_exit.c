#include "../../../inc/minishell.h"

static void	check_argument(char *str)
{
	char	*buf;

	buf = str;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n", buf);
			exit (2);
		}
		str++;
	}
}

int builtin_exit(char **args)
{
	if (!args[1])
	{
		garbage_free_all();
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (args[2])
		{
			ft_fprintf(2, "bash: exit: too many arguments\n");
			return (0);
		}
		else
			check_argument(args[1]);
		exit (ft_atoi(args[1]));
	}
}

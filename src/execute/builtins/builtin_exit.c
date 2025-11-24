#include "../../../inc/minishell.h"

static void	check_argument(char *str)
{
	char	*buf;

	buf = str;
	while (*str)
	{
		if (*str == '-' || *str == '+')
			str++;
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
	long long	exit_code;

	if (!args[1])
	{
		garbage_free_all();
		ft_fprintf(1, "exit");
		exit(0);
	}
	else
	{
		if (args[2])
		{
			ft_fprintf(2, "bash: exit: too many arguments\n");
			if (ft_isdigit(args[1][0]))
				exit (1);
			exit (2);
		}
		else
		{
			
		}
			check_argument(args[1]);
		exit_code = ft_atol(args[1]);
		if (exit_code < 0)
			exit_code = 256 + (exit_code % 256);
		exit (exit_code);
	}
}

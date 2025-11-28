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
			ft_fprintf(STDERR_FILENO,
				"exit: %s: numeric argument required\n", buf);
			exit (2);
		}
		str++;
	}
}

int	builtin_exit(char **args)
{
	long long	exit_code;

    // garbage_free_all();
	if (!args[1])
		exit(0);
	if (args[2])
	{
		ft_fprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
		if (ft_isdigit(args[1][0]))
			exit(1);
		exit(2);
	}
	if (!args[1][0])
	{
		ft_fprintf(STDERR_FILENO,
			"bash: exit: : numeric argument required\n");
		exit(2);
	}
	check_argument(args[1]);
	exit_code = ft_atol(args[1]);
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	exit(exit_code);
}

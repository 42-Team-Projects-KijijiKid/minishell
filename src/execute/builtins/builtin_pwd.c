#include "../../../inc/minishell.h"

int	builtin_pwd(char **args)
{
	char	*pwd;

	(void)args;
	pwd = env_get_value("PWD");
	if (!pwd)
		ft_error("pwd: PWD not set", __FILE__, __LINE__, 930);
	ft_fprintf(1, "%s\n", pwd);
	return (0);
}

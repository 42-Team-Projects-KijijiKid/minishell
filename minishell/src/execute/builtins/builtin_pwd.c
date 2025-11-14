#include "../../../inc/minishell.h"

int builtin_pwd(char **args)
{
	char *pwd;

	pwd = env_get_value("PWD");
	if (!pwd)
		ft_error("pwd: PWD not set", __FILE__, __LINE__, 930);
	if (printf("%s\n", pwd) < 0) // TODO: Prototyp printf error handling; erase or implement others
		ft_error("printf failed", __FILE__, __LINE__, 932);
	return (0);
}

/*int builtin_pwd(char **args)
{
	char buf[4096];
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}*/

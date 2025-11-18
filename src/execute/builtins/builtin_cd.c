#include "../../../inc/minishell.h"

static char	*build_path(void)
{
	return (NULL);
}

/*Improved change directory*/

int	builtin_cd(char **args)
{
	char	*new_pwd;
	char	*old_pwd;
	
	old_pwd = get_environment_value("PWD");
	if (!args[1])
		new_pwd = get_environment_value("HOME");
	else
		new_pwd = build_path();
	if (chdir(new_pwd) == 0)
	{
		env_set_value("PWD", new_pwd);
		env_set_value("OLDPWD", old_pwd);
	}
	else
	{
		error_msg("cd: aslkdm: No such file or directory", __FILE__, __LINE__);
		return (128);
	}
	
	return (0);
}

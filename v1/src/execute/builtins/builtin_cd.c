#include "../../../inc/minishell.h"

char	*build_new_pwd(char	*current_pwd, char *relative_path)
{
	char	*new_pwd;
	if (relative_path[0] == '/')
	{
		new_pwd = ft_strdup(relative_path); // New version required, that adds to garbage collector
	}
	else
	{
		new_pwd = ft_strjoin(current_pwd, "/"); // New version required, that adds to garbage collector
		new_pwd = ft_strjoin(new_pwd, relative_path); // New version required, that adds to garbage collector
	}
	return (new_pwd);
}

int builtin_cd(char **args)
{
	char	*current_pwd;
	char	*new_pwd;
	char	*error;

	if (!args || !args[0])
		return (ft_error("cd: invalid arguments", __FILE__, __LINE__, 920), 920);
	current_pwd = env_get_value("PWD");
	if (!current_pwd)
		return (ft_error("cd: PWD not set", __FILE__, __LINE__, 921), 921);
	env_set_value("OLDPWD", current_pwd);
	if (!args[1])
	{
		new_pwd = env_get_value("HOME");
		if (!new_pwd)
			return (ft_error("cd: HOME not set", __FILE__, __LINE__, 921), 921);
	}
	else
	{
		if (args[1][0] == '/')
			new_pwd = ft_strdup(args[1]); // New version required, that adds to garbage collector
		else
		{
			new_pwd = build_new_pwd(current_pwd, args[1]);
			if (!new_pwd)
				return (ft_error("cd: memory allocation failed", __FILE__, __LINE__, 923), 923);
		}
	}
	if (chdir(new_pwd) == -1)
	{
		error = ft_strjoin("cd: no such file or directory: ", new_pwd); // New version required, that adds to garbage collector
		return (ft_error(error, __FILE__, __LINE__, 922), 922);
	}
	env_set_value("PWD", new_pwd);
	return (0);
}

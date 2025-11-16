#include "../../../inc/minishell.h"

char	*build_new_pwd(char	*current_pwd, char *relative_path)
{
	char	*new_pwd;
	int		i;

	if (relative_path[0] == '/')
		new_pwd = fti_strdup(relative_path); // TODO: New version required, that adds to garbage collector
	else
	{
		new_pwd = fti_strjoin(current_pwd, "/"); // TODO: New version required, that adds to garbage collector
		new_pwd = fti_strjoin(new_pwd, relative_path); // TODO: New version required, that adds to garbage collector
	}
	i = ft_strlen(new_pwd);
	while (new_pwd[--i] == '/')
		new_pwd[i] = '/';
	return (new_pwd);
}

int	builtin_cd(char **args)
{
	char	*current_pwd;
	char	*new_pwd;
	char	*error;

	current_pwd = env_get_value("PWD");
	if (!current_pwd)
		ft_error("cd: PWD not set", __FILE__, __LINE__, 921);
	env_set_value("OLDPWD", current_pwd);
	if (!args[1])
	{
		new_pwd = env_get_value("HOME");
		if (!new_pwd)
			ft_error("cd: HOME not set", __FILE__, __LINE__, 921);
	}
	else
	{
		new_pwd = build_new_pwd(current_pwd, args[1]);
		if (!new_pwd)
			ft_error("cd: memory allocation failed", __FILE__, __LINE__, 923);
	}
	if (chdir(new_pwd) == -1)
	{
		error = fti_strjoin("cd: no such file or directory: ", new_pwd); // TODO: New version required, that adds to garbage collector
		ft_error(error, __FILE__, __LINE__, 922);
	}
	env_set_value("PWD", new_pwd);
	return (0);
}

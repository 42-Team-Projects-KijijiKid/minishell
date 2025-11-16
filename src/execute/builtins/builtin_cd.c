#include "../../../inc/minishell.h"

char	*go_home(void)
{
	char *new_pwd;

	new_pwd = env_get_value("HOME");
	return (new_pwd);
}

char	*go_back(char *current_pwd)
{
	int		len;
	char	*new_pwd;

	if (current_pwd == '/')
		return (current_pwd);
	len = ft_strlen(current_pwd) - 1;
	while (current_pwd[len] != '/')
		len--;
	if (len == 0)
	{
		env_set_value("PWD", "/");
		new_pwd = fti_strdup("/");
		return (new_pwd);
	}
	new_pwd = fti_malloc(sizeof(char) * len, TEMPORARY);
	new_pwd[len] = '\0';
	len--;
	while (0 <= len)
	{
		new_pwd[len] = current_pwd[len];
		len--;
	}
	return (new_pwd);
}

char	*build_new_pwd(char	*current_pwd, char *relative_path)
{
	char	*new_pwd;
	int		i;
	int		rel_path_len;

	rel_path_len = ft_strlen(relative_path);
	if (strncmp(relative_path, "..", rel_path_len) == 0
		&& rel_path_len == 2)
		new_pwd = go_back(current_pwd);
	else if (strncmp(relative_path, "~", rel_path_len) == 0
		&& rel_path_len == 1)
		new_pwd = go_home();
	// else if (strncmp(relative_path, "/", rel_path_len) == 0
	// 	&& rel_path_len == 1)
	// 	new_pwd = go_root();
	// else
	// 	new_pwd = change_by_name();
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

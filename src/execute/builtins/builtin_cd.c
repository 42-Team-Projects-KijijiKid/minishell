#include "../../../inc/minishell.h"

static int	len_until_slash(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '/')
		i++;
	return (i);
}

static int	count_go_back(char *new_path)
{
	int	len;
	int	double_dot_count;

	len = 2;
	double_dot_count = 0;
	while (new_path)
	{
		new_path += len;
		if (*new_path == '\0')
			return (double_dot_count);
		if (new_path && *new_path == '/')
			new_path++;
		len = len_until_slash(new_path);
		if (2 < len)
		{
			error_msg("cd: No such file or directory", __FILE__, __LINE__);
			return (139);
		}
		else if (len == 2)
			double_dot_count++;
	}
	return (double_dot_count);
}

static char	*cut_till_slash(char *current_pwd)
{
	int	len;

	len = ft_strlen(current_pwd) - 1;
	while (current_pwd[len] && current_pwd[len] != '/')
		len--;
	if (!current_pwd)
		return ("/");
	else
	{
		current_pwd[len] = '\0';
		current_pwd = fti_strdup(current_pwd, TEMPORARY);
	}
	return (current_pwd);
}

static char	*go_dir_back(char *current_pwd, char *new_path)
{
	int	go_back_count;

	go_back_count = count_go_back(new_path);
	printf("Go Back Cnt: %d\n", go_back_count);
	while (0 <= go_back_count)
	{
		new_path = cut_till_slash(current_pwd);
		printf("New Path: %s\n", new_path);
		go_back_count--;
	}
	return (new_path);
}

static char	*build_path(char *current_pwd, char *new_path)
{
	if (!ft_strncmp(current_pwd, new_path, ft_strlen(new_path)))
		new_path = fti_strdup(new_path, TEMPORARY);
	else if (!ft_strncmp(new_path, "..", 2))
		new_path = go_dir_back(current_pwd, new_path);
	return (new_path);
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
	{
		if (!args[2])
			new_pwd = build_path(old_pwd, args[1]);
		else
		{
			error_msg("cd: too many arguments", __FILE__, __LINE__);
			return (129);
		}
	}
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

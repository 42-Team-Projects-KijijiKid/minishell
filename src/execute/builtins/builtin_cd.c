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
			ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", new_path);
			return (-1);
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
	if (len == -1)
		return (fti_strdup("/", TEMPORARY));
	if (len != 0 && current_pwd[len] == '/')
		len--;
	while (current_pwd[len] && current_pwd[len] && current_pwd[len] != '/')
		len--;
	current_pwd[len] = '\0';
	if (!*current_pwd)
		return (fti_strdup("/", TEMPORARY));
	current_pwd = fti_strdup(current_pwd, TEMPORARY);
	return (current_pwd);
}

static char	*go_dir_back(char *current_pwd, char *new_path)
{
	int	go_back_count;

	go_back_count = count_go_back(new_path);
	while (0 <= go_back_count)
	{
		new_path = cut_till_slash(current_pwd);
		go_back_count--;
	}
	return (new_path);
}

static char *concatenate_paths(char *current_pwd, char *new_path)
{
	int		len;
	char	*rtn;

	len = ft_strlen(current_pwd) - 1;
	if (current_pwd[len] != '/')
	{
		rtn = fti_strjoin(current_pwd, "/");
		rtn = fti_strjoin(rtn, new_path);
	}
	else
	{
		if (*new_path != '/')
			rtn = fti_strjoin("/", new_path);
		else
			rtn = fti_strdup(new_path, TEMPORARY);
	}
	return (rtn);
}


static char	*build_path(char *current_pwd, char *new_path)
{
	int i;

	i = 0;
	while (new_path[i + 1])
		i++;
	if (new_path[i] == '/')
		new_path[i] = '\0';
	if (!ft_strncmp(current_pwd, new_path, ft_strlen(new_path)))
		new_path = fti_strdup(new_path, TEMPORARY);
	else if (!ft_strncmp(new_path, "..", 2))
		new_path = go_dir_back(current_pwd, new_path);
	else
		new_path = concatenate_paths(current_pwd, new_path);
	return (new_path);
}

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
			ft_fprintf(2, "cd: too many arguments\n");
			return (1);
		}
	}
	if (chdir(new_pwd) == 0)
	{
		env_set_value("PWD", new_pwd);
		env_set_value("OLDPWD", old_pwd);
	}
	else
	{
		ft_fprintf(STDERR_FILENO ,"cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	return (0);
}

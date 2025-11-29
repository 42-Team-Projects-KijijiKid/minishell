#include "../../../inc/minishell.h"

static char	*go_dir_back(char *current_pwd, char *new_path)
{
	int	go_back_count;
	int	dot_count;

	dot_count = len_until_slash(new_path);
	if (2 != dot_count)
		return (new_path);
	go_back_count = count_go_back(new_path);
	while (0 <= go_back_count)
	{
		new_path = cut_till_slash(current_pwd);
		go_back_count--;
	}
	return (new_path);
}

static char	*concatenate_paths(char *current_pwd, char *new_path)
{
	int		len;
	char	*rtn;

	len = ft_strlen(current_pwd) - 1;
	if (current_pwd[len] != '/')
	{
		rtn = fti_strjoin(current_pwd, "/", TEMPORARY);
		rtn = fti_strjoin(rtn, new_path, TEMPORARY);
	}
	else
	{
		if (*new_path != '/')
			rtn = fti_strjoin("/", new_path, TEMPORARY);
		else
			rtn = fti_strdup(new_path, TEMPORARY);
	}
	return (rtn);
}

static char	*build_path(char *current_pwd, char *new_path)
{
	int	i;

	i = 0;
	while (new_path[i + 1])
		i++;
	if (new_path[i] == '/')
		new_path[i] = '\0';
	if (*new_path == '/')
		new_path = fti_strdup(new_path, TEMPORARY);
	else if (!ft_strncmp(new_path, "..", 2))
		new_path = go_dir_back(current_pwd, new_path);
	else if (!ft_strncmp(new_path, ".", 1))
		new_path = current_pwd;
	else if (!ft_strncmp(new_path, "-", 1))
		new_path = env_get_value("OLDPWD");
	else
		new_path = concatenate_paths(current_pwd, new_path);
	return (new_path);
}

static void	set_env(char *new_pwd, char *old_pwd)
{
	env_set_value("PWD", new_pwd);
	env_set_value("OLDPWD", old_pwd);
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
			ft_fprintf(2, CD_TO_MANY_ARGS);
			return (1);
		}
	}
	if (chdir(new_pwd) == 0)
		set_env(new_pwd, old_pwd);
	else
	{
		ft_fprintf(STDERR_FILENO, NO_FILE_DIR, "cd", args[1]);
		return (1);
	}
	return (0);
}

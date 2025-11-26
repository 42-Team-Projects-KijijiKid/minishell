#include "minishell.h"

int	len_until_slash(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '/')
		i++;
	return (i);
}

int	count_go_back(char *new_path)
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
			ft_fprintf(STDERR_FILENO, NO_FILE_DIR, "cd", new_path);
			return (-1);
		}
		else if (len == 2)
			double_dot_count++;
	}
	return (double_dot_count);
}

char	*cut_till_slash(char *current_pwd)
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

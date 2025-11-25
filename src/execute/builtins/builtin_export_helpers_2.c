#include "minishell.h"

char	*extract_key(char *str)
{
	char		*rtn;
	int			i;
	t_minishell	*shell;

	i = 0;
	shell = minishell_get();
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	rtn = fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	ft_strlcpy(rtn, str, (i + 1));
	return (rtn);
}

char	*extract_value(char *str)
{
	char		*rtn;
	int			i;
	t_minishell	*shell;

	i = 0;
	shell = minishell_get();
	while (*str && *str != '+'
			&& *str != '=')
		str++;
	if (*str && *str == '+')
		str++;
	if (*str && *str == '=')
		str++;
	i = 0;
	while (str[i])
		i++;
	rtn = fti_malloc(sizeof(char) * (i + 1), TEMPORARY);
	ft_strlcpy(rtn, str, i + 1);
	return (rtn);
}

#include "../../../inc/minishell.h"

unsigned int	strlen_with_expansion(char *str, char quote)
{
	int		len_1;
	int		len_2;
	char	*tmp_str;

	len_1 = 0;
	len_2 = 0;
	while (*str != quote && *str)
	{
		if (*str == '$')
		{
			str++;
			tmp_str = null_end_str(&str);
			tmp_str = get_environment_value(tmp_str);
			if (tmp_str)
				len_2 += ft_strlen(tmp_str);
		}
		if (*str && *str != quote)
			len_1++;
		if (*str && *str != '$')
			str++;
	}
	return (len_1 + len_2);
}

char	*last_exit_code(void)
{
	t_minishell	*shell;

	shell = minishell_get();
	return (fti_itoa(shell->last_exit_status));
}

char	*give_env_str(char **str)
{
	char	*tmp;
	char	*rtn;

	if (**str == '$')
		(*str)++;
	else
		return (NULL);
	tmp = null_end_str(str);
	if (!*tmp)
		return (NULL);
	if (ft_strncmp(tmp, "?", ft_strlen(tmp)) == 0)
		return (last_exit_code());
	rtn = get_environment_value(tmp);
	return (rtn);
}

char	*expand_inside_str(char *str, char quote)
{
	char	*rtn;
	char	*tmp_str;
	int		i;

	rtn = fti_malloc((sizeof(char) * strlen_with_expansion(
					str, quote)) + 1, TEMPORARY);
	i = 0;
	while (*str != quote && *str)
	{
		if (*str == '$')
		{
			tmp_str = give_env_str(&str);
			while (tmp_str && *tmp_str)
			{
				rtn[i++] = *tmp_str;
				tmp_str++;
			}
		}
		if (*str != quote && *str
			&& *str != '$')
			rtn[i++] = *str;
		if (*str && *str != '$')
			str++;
	}
	return (rtn[i] = '\0', rtn);
}

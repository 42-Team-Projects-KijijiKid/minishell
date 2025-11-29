#include "minishell.h"

bool	env_value(char **str, char *rtn, int *i)
{
	char	*tmp_str;

	tmp_str = give_env_str(str);
	while (tmp_str && *tmp_str)
	{
		rtn[*i] = *tmp_str;
		(*i)++;
		tmp_str++;
	}
	if (!tmp_str)
		return (false);
	return (true);
}

bool	is_whitespace(char ch)
{
	if (ch == 32 || (9 <= ch && ch <= 13))
		return (true);
	return (false);
}

bool	check_char(char *str)
{
	str++;
	if (*str == '\0')
		return (false);
	else
		return (true);
	return (false);
}

bool	quote_has_content(char *str)
{
	char	quote;

	if (*str != '\''
		|| *str != '\"')
		return (true);
	quote = *str;
	str++;
	if (quote == *str)
		return (false);
	while (*str != quote && *str)
		str++;
	return (true);
}

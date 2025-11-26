#include "minishell.h"

void	process_non_dollar(char **str, char *rtn, int *i, bool (*quotes)[2])
{
	if (!quote_has_content(*str) && (!(*quotes)[0] || !(*quotes)[1]))
		*str += 2;
	else if (**str == '\'' && !(*quotes)[0])
	{
		(*quotes)[1] = !(*quotes)[1];
		(*str)++;
	}
	else if (**str == '\"' && !(*quotes)[1])
	{
		(*quotes)[0] = !(*quotes)[0];
		(*str)++;
	}
	else if (**str && **str != '\\')
	{
		rtn[*i] = **str;
		(*i)++;
		(*str)++;
	}
	else
	{
		if (**str == '\\')
			(*str)++;
		rtn[(*i)++] = **str;
		(*str)++;
	}
}

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

bool	check_if_valid(char *str)
{
	str++;
	if (*str == '\0')
		return (false);
	else
		return (true);
	return (false);
}

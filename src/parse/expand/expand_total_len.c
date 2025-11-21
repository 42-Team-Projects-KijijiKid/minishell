#include "minishell.h"

static unsigned int	give_env_len(char **str)
{
	char *tmp;
	unsigned int len;

	tmp = give_env_str(str);
	if (tmp)
		len = ft_strlen(tmp);
	else
		len = 0;
	return (len);
}

static int	process_non_dollar(char **sp, bool *single_quotes, bool *double_quotes)
{
	if (!quote_has_content(*sp) && (!*single_quotes || !*double_quotes))
		*sp += 2;
	else if (**sp == '\'' && !*double_quotes)
	{
		*single_quotes = !*single_quotes;
		(*sp)++;
	}
	else if (**sp == '\"' && !*single_quotes)
	{
		*double_quotes = !*double_quotes;
		(*sp)++;
	}
	else if (**sp)
	{
		(*sp)++;
		return (1);
	}
	return (0);
}

static bool	check_if_valid(char *str)
{
	str++;
	if (*str == '\0')
		return (false);
	else
	{
		if (ft_isalpha(*str)
			|| *str == '?')
			return (true);
	}
	return (false);
}

unsigned int	total_length(char *str)
{
	int		total_len;
	bool	single_quotes;
	bool	double_quotes;

	total_len = 0;
	single_quotes = false;
	double_quotes = false;
	while (*str)
	{
		if (*str == '$' && !single_quotes
			&& check_if_valid(str))
			total_len += give_env_len(&str);
		else
			total_len += process_non_dollar(&str, &single_quotes, &double_quotes);
	}
	return (total_len);
}

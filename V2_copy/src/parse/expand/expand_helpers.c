#include "minishell.h"

/// @brief Pass the string not beginning with the qoute
/// and count how many chars are inside the string
/// without the counting of the matching quote
int	strlen_whitout_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (*str != quote && str)
	{
		str++;
		i++;
	}
	return (i);
}

/// @brief Null ends a possible expansion
/// string isolate from rest of the string
/// @param str str thats in quotes
/// @return isolated string
char	*null_end_str(char **str)
{
	int		i;
	char	*rtn;

	rtn = *str;
	i = 0;
	while ((*str)[i] && (*str)[i] != ' ' && !is_meta_char((*str)[i])
			&& (*str)[i] != '$' && (*str)[i] != '\"'
			&& (*str)[i] != '\'')
		i++;
	rtn = fti_malloc((sizeof(char) * i) + 1, TEMPORARY);
	i = 0;
	while (**str && **str != ' ' && !is_meta_char(**str)
			&& **str != '$' && **str != '\"'
			&& **str != '\'')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	if (**str && **str == '\"')
		(*str)++;
	rtn[i] = '\0';
	return (rtn);
}

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
				len_2 = ft_strlen(tmp_str);
		}
		if (*str && *str != quote)
			len_1++;
		if (*str && *str != '$')
			str++;
	}
	int tmp = len_1+ len_2;
	return (len_1 + len_2);
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
	rtn = get_environment_value(tmp);
	return (rtn);
}

char	*expand_inside_str(char *str, char quote)
{
	char	*rtn;
	char	*tmp_str;
	int		i;

	rtn = fti_malloc((sizeof(char) * strlen_with_expansion(str, quote)) + 1, TEMPORARY);
	i = 0;
	while (*str != quote && *str)
	{
		if (*str == '$')
		{
			tmp_str =  give_env_str(&str);
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
	rtn[i] = '\0';
	return (rtn);
}

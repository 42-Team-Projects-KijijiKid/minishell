#include "parsing.h"


/// @brief Null ends a possible expansion
/// string isolate from rest of the string
/// @param str str thats in quotes
/// @return isolated string
char	*null_end_str(char **str)
{
	int		i;
	char	*rtn_str;

	i = 0;
	rtn_str = *str;
	while (*str && **str != ' ' && !is_meta_char(**str))
	{
		(*str)++;
		i++;
	}
	rtn_str[i] = '\0';
	return (rtn_str);
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
			len_2 = ft_strlen(rtn_env_value(tmp_str));
		}
		else
			len_1++;
		str++;
	}
	return (len_1 + len_2);
}

char	*expand_inside_str(char *str, char quote)
{
	printf("Expanded Len: %d\n", strlen_with_expansion(str, quote));
	// while (*str != *quote)
	// {

	// }
	return (NULL);
}

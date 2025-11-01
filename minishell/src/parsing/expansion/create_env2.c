#include "parsing.h"

/// @brief return the len to the
/// equal sign 
/// @param str 
/// @return length of cahrs till equal sign
unsigned int	len_to_equal(char *str)
{
	unsigned int	i;

	i = 0;
	while (*str != '=')
	{
		str++;
		i++;
	}
	return (i);
}

/// @brief Abstracts the key of env var
/// Skips away the equal sign so
/// abstract_value can begin copy directly
/// @param str 
/// @return NULL terminated key
/// without the equal sign
char	*abstract_key(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = len_to_equal(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_1);
	i = 0;
	while (**str != '=')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	if (**str == '=')
		(*str)++;
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Asbtarcts the value of env var
/// @param str 
/// @return NULL terminated value 
/// without the equal sign
char	*abstract_value(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = ft_strlen(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_1);
	i = 0;
	while (**str)
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

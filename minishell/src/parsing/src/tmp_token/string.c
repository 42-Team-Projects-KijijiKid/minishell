#include "parsing.h"

unsigned int		len_to_quotes(char *str)
{
	unsigned int i;

	i = 0;
	while (1)
	{
		i++;
		str++;
		if (*str == '\'' || *str == '\"')
		{
			i++;
			break ;
		}
	}
	return (i);
}

char	*str_in_quotes(char **str)
{
	unsigned int	i;
	char			*rtn;
	
	i = len_to_quotes(*str);
	rtn = ft_malloc((sizeof(char) * i) + 1, LAYER_2);
	i = 0;
	while (1)
	{
		rtn[i] = **str;
		i++;
		(*str)++;
		if (**str == '\'' || **str == '\"')
		{
			rtn[i] = **str;
			i++;
			(*str)++;
			break ;
		}
	}
	rtn[i] = '\0';
	return (rtn);
}

#include "parsing.h"

unsigned int		len_to_quotes(char *str)
{
	unsigned int i;
	char		*quote_end;

	i = 0;
	quote_end = str;
	while (1)
	{
		i++;
		str++;
		if (*str == *quote_end)
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
	char			*quote_end;
	
	i = len_to_quotes(*str);
	rtn = ft_malloc((sizeof(char) * i) + 1, LAYER_2);
	i = 0;
	quote_end = *str;
	while (1)
	{
		rtn[i] = **str;
		i++;
		(*str)++;
		if (**str == *quote_end)
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

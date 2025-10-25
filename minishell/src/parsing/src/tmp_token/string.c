#include "parsing.h"

char	*rtn_str_quotes(char **str, t_meta *meta)
{
	int		i;
	char	*rtn;
	i = 0;
	while (1)
	{
		i++;
		if(*str[i] == '\'' || *str[i] == '\"')
		{
			i++;
			break;
		}
	}
	rtn = malloc((sizeof(char) * i) + 1);
	add_to_layer(meta->layer_2, rtn);
	i = 0;
	while (1)
	{
		rtn[i] = *str[i];
		i++;
		if(*str[i] == '\'' || *str[i] == '\"')
		{
			rtn[i] = *str[i];
			i++;
			break;
		}
	}
	rtn[i] = '\0';
	return (rtn);
}
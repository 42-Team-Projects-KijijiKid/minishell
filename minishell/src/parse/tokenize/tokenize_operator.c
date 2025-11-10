#include "../../../inc/minishell.h"

char	**tokenize_operator(char **str)
{
	char	**rtn;
	char	next_char;

	if (*(*str + sizeof(char)))
		next_char = *(*str + sizeof(char));
	rtn = fti_malloc(sizeof(char *) * 2, TEMPORARY);
	if (is_meta_char(**str) && **str == next_char)
	{
		rtn[0] = fti_malloc((sizeof(char) * 2) + 1, TEMPORARY);
		rtn[0][0] = **str;
		(*str)++;
		rtn[0][1] = **str;
		(*str)++;
		rtn[0][2] = '\0';
	}
	else
	{
		rtn[0] = fti_malloc((sizeof(char) * 1) + 1, TEMPORARY);
		rtn[0][0] = **str;
		(*str)++;
		rtn[0][1] = '\0';
	}
	rtn[1] = NULL;
	return (rtn);
}

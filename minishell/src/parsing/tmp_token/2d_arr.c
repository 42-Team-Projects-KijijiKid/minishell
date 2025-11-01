#include "parsing.h"

/// @brief This function skips
/// every space and moves
/// the pointer pointer
void	skip_space(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

/// @brief Counts the leght of a single str
/// delimited by meta chars space or asterix(-)
/// @param str 
/// @return len of str
int	len_of_str(char *str)
{
	int	i;

	i = 0;
	while (*str && !is_meta_char(*str)
			&& *str != '-'
			&& *str != ' ')
	{
		i++;
		str++;
	}
	return (i);
}

char	*normal_str(char **str)
{
	int		i;
	int		len;
	char	*rtn;

	len = len_of_str(*str);
	rtn = ft_malloc((sizeof(char) * len) + 1, LAYER_2);
	i = 0;
	while (**str && !is_meta_char(**str)
			&& **str != ' ')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*give_word(char **str)
{
	char	*rtn;

	while (**str)
	{
		skip_space(str);
		if (**str == '\'' || **str == '\"')
			return (str_in_quotes(str));
		else
			return (normal_str(str));
	}
	return (rtn);
}

/// @brief This function creates 2D array with 
/// till end of provided command or if an operator
/// is reached. Handles also the quote rules checking
/// for quotes without content therefore earasing them.
/// Does not handle expansion!
/// @param str Command
/// @return A split up 2D array with applied 
/// bash rules for quotes till end or 
/// an operator is reached
char	**special_split(char **str)
{
	int		i;
	char	**rtn;
	int		words;

	words = word_count(*str);
	rtn = ft_malloc((sizeof(char *) * words) + 1, LAYER_2);
	i = 0;
	while (i < words)
	{
		rtn[i] = give_word(str);
		i++;
	}
	// printf("IDE: %s\n", rtn[0][1]);
	rtn[i] = NULL;
	return (rtn);
}

// char	**give_2d_arg(char **str)
// {
// 	char	**rtn;

// 	rtn = special_split(str);
// 	return (rtn);
// }

// int main(void)
// {
// 	char * str= "ls -l | grep a";
// 	char **splitted;

// 	splitted = give_2d_arg(&str);
// 	printf("[");
// 	while (*splitted)
// 	{
// 		if (splitted)
// 			printf("%s, ", *splitted);
// 		splitted++;
// 	}
// 	printf("]\n");
// }
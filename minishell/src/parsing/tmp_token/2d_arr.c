#include "parsing.h"

/// @brief Checks if the quote pair has
/// content so its not '' or "".
/// @param str 
/// @return false if there is no quote conentet
/// true if there is quote content
bool	quote_content(char **str)
{
	char	quote;

	printf("Content: %c\n", **str);
	quote = **str;
	(*str)++;
	printf("Content:2 %c\n", **str);
	if (quote == **str)
		return (false);
	while (**str != quote && **str)
		(*str)++;
	return (true);
}

/// @brief Count words till operator
/// or end of str handling quotes.
/// @param str 
/// @return amount of words till operator
/// or null termination
int	word_count(char *str)
{
	int		words;
	bool	flag;

	words = 0;
	flag = true;
	while (*str)
	{	
		if (flag && *str == '\'' || *str == '\"')
		{
			if (quote_content(&str))
				words++;
		}
		else if (flag && *str != ' '
			&& !is_meta_char(*str))
		{
			flag = false;
			words++;
		}
		else if (*str == ' ')
			flag = true;
		str++;
	}
	return (words);
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
	printf("Words: %d\n", words);
	// rtn = ft_malloc(sizeof(char *) * (words + 1), LAYER_2);
	// i = 0;
	// while (i < words)
	// {
	// 	rtn[i] = give_word(str);
	// 	i++;
	// }
	// rtn[i] = NULL;
	exit(101);
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
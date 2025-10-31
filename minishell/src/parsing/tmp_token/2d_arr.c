#include "parsing.h"

unsigned int		len_to_quotes(char *str)
{
	unsigned int i;
	char		quote_end;

	i = 0;
	quote_end = *str;
	while (*str)
	{
		i++;
		str++;
		if (*str == quote_end)
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
	char			quote_end;
	
	i = len_to_quotes(*str);
	rtn = ft_malloc((sizeof(char) * i) + 1, LAYER_2);
	i = 0;
	quote_end = **str;
	while (**str)
	{
		rtn[i] = **str;
		i++;
		(*str)++;
		if (**str == quote_end)
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

/// @brief This function skips
/// every space and moves
/// the pointer pointer
void	skip_space(char **str)
{
	while (**str && **str != ' ')
		(*str)++;
}

/// @brief Checks if the quote pair has
/// content so its not '' or "".
/// Does not skips the content.
/// @return false if there is no quote content
/// true if there is quote content
bool	check_for_content(char *str)
{
	char	quote;
	
	quote = *str;
	str++;
	if (quote == *str)
		return (false);
	return (true);
}

/// @brief This goes trough the
/// string skipping space characters
/// or emty quotes
/// @param str 
void	skip_invalid(char **str)
{
	while (**str && !is_meta_char(**str))
	{
		skip_space(str);
		if (**str == '\'' || **str == '\"')
		{
			if (!check_for_content(*str))
			{
				(*str)++;
				(*str)++;
				continue ;
			}
			else
				break ;
		}
		else
			break ;
		(*str)++;
	}
}

int	len_to_space(char *str)
{
	int	i;

	i = 0;
	while (*str && *str != ' ')
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

	len = len_to_space(*str);
	rtn = ft_malloc((sizeof(char) * len) + 1, LAYER_2);
	i = 0;
	while (**str != ' ' && **str)
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
		skip_invalid(str);
		if (**str == '\''
			|| **str == '\"')
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
	printf("Str: %s\n", *str);
	printf("Words: %d\n", words);
	rtn = ft_malloc((sizeof(char *) * words) + 1, LAYER_2);
	i = 0;
	while (i < words)
	{
		rtn[i] = give_word(str);
		i++;
	}
	printf("IDE: %s\n", rtn[1]);
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
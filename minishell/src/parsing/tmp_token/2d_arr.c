#include "parsing.h"

int	word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i]
			&& (!is_meta_char(*str) || *str == '\"' || *str == '\''))
		i++;
	return (i);
}

char	*give_word(char **str)
{
	char	*rtn;
	int		i;
	int		len;

	while (**str == ' ')
		(*str)++;
	if (**str == '\"' || **str == '\'')
		return (str_in_quotes(str));
	len = word_len(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_2);
	i = 0;
	while (**str && i < len)
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Moves the pointer till reaches the
/// matching quote pair
/// @param str the adress of the current
/// cmd string
void	go_trough_quoted_str(char **str)
{
	char	quote_end;
	
	quote_end = **str;
	while (1)
	{
		(*str)++;
		if (**str == quote_end)

			break ;
	}
}

int	word_count(char *str)
{
	int	words;
	int	flag;

	words = 0;
	flag = 1;
	while (*str && !is_meta_char(*str))
	{
		if (flag && (*str == '-'
			|| ft_isalpha(*str)))
		{
			flag = 0;
			words++;
		}
		if (*str == ' ')
			flag = 1;
		str++;
	}
	return (words);
}

char	**special_split(char **str)
{
	int		i;
	char	**rtn;
	int		words;

	words = word_count(*str);
	rtn = ft_malloc(sizeof(char *) * (words + 1), LAYER_2);
	i = 0;
	while (i < words)
	{
		rtn[i] = give_word(str);
		i++;
	}
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
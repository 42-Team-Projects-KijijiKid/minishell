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

int	word_count(char *str)
{
	int		flag;
	int		count;
	char	quote_end;

	count = 0;
	flag = 1;
	while ((!is_meta_char(*str) || *str == '\"' || *str == '\'') && *str)
	{
		if ((*str == '\"' || *str == '\''))
		{
			quote_end = *str;
			count++;
			while (1)
			{
				str++;
				if (*str == quote_end)
					break ;
			}
		}
		else if (*str != ' ' && flag)
		{
			count++;
			flag = 0;
		}
		if (*str == ' ')
			flag = 1;
		str++;
	}
	return (count);
}

char	**special_split(char **str)
{
	int		i;
	char	**rtn;
	int		words;

	words = word_count(*str);
	rtn = ft_malloc(sizeof(char *) * (word_count(*str) + 1), LAYER_2);
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
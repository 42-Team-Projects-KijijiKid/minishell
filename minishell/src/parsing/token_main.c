#include "parsing.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*word_back(char *cmd)
{
	int		i;
	char	*str;

	i = ft_strlen(cmd);
	str = malloc(sizeof(char)*i);
	while (('0' <= *cmd &&  *cmd <= '9') || ('a' <= *cmd && *cmd <= 'z')
		|| ('A' <= *cmd && *cmd <= 'Z'))
	{
		*str = *cmd;
		str++;
		cmd++;
	}
	return (str);
}

t_token	*create_tokens(char *cmd)
{
	t_token	*cmd_list;
	while (*cmd)
	{
		cmd_list = malloc(sizeof(t_token));
		cmd_list->value = word_back(cmd);
		break ;
	}
	printf("Create Tokens: %s\n", cmd_list->value);
}

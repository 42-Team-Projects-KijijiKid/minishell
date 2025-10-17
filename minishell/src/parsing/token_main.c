#include "parsing.h"

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_token	*create_tokens(char *cmd)
{
	t_token	*begin;
	t_token	*cmd_list;
	t_token *tmp;

	tmp = NULL;
	while (*cmd)
	{
		cmd_list = malloc(sizeof(t_token));
		if (tmp)
			tmp->left = cmd_list;
		cmd_list->value = abstract_value(cmd);
		tmp = cmd_list;
		cmd_list = cmd_list->left;
	}
	printf("Create Tokens: %s\n", cmd_list->value);
}

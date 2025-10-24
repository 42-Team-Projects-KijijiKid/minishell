#include "parsing.h"

static char	*conv_type_enums(t_token_enum token_type)
{
	char *str;
	char *rtn;

	if (token_type == 0)
		str = "Text\0";
	else if (token_type == 1)
		str = "Pipe\0";
	else if (token_type == 2)
		str = "&& Operator\0";
	else if (token_type == 3)
		str = "|| Operator\0";
	else if (token_type == 4)
		str = "In redirection\0";
	else if (token_type == 5)
		str = "Out redirection\0";
	else if (token_type == 6)
		str = "Append\0";
	else if (token_type == 7)
		str = "Heredoc\0";
	rtn = ft_strdup(str);
	return (rtn);
}

void	print_tokens(t_token *token)
{
	char *type_buff;

	while (token)
	{
		type_buff = conv_type_enums(token->type);
		printf("Type: %s\n", type_buff);
		if (token->value)
			printf("Value: %s\n", token->value);
		else
		{
			printf("[");
			while (*token->args_2d)
			{
				printf("%s, ", *token->args_2d);
				token->args_2d++;
			}
			printf("]");
		}
		printf("-------------\n");
		free(type_buff);
		token = token->left;
	}
}

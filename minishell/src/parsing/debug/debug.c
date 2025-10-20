#include "parsing.h"

static char	*conv_type_enums(t_token_enum *token_type)
{
	char *str;
	char *rtn;

	if (token_type == T_TEXT)
		str = "Text\0";
	else if (token_type == T_PIPE)
		str = "Pipe\0";
	else if (token_type == T_AND)
		str = "&& Operator\0";
	else if (token_type == T_OR)
		str = "|| Operator\0";
	else if (token_type == T_IN_RDR)
		str = "In redirection\0";
	else if (token_type == T_OUT_RDR)
		str = "Out redirection\0";
	else if (token_type == T_APPEND)
		str = "Append\0";
	else if (token_type == T_HEREDOC)
		str = "Heredoc\0";
	rtn = malloc(ft_strlen(str + 1));
	rtn = str;
	return (rtn);
}

void	print_tokens(t_token *token)
{
	char *type_buff;

	while (token)
	{
		type_buff = conv_type_enums(token->type);
		printf("Type: %s", type_buff);
		printf("---\\\n");
		printf("Value: %s\n", token->value);
		printf("---/\n");
		free(type_buff);
	}
}

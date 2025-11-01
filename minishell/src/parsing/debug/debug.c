#include "parsing.h"

void	print_2d_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/// @brief Prints the key && value pairs 
/// from tail to head (so they are shown in 
/// the right order)
void	print_env(void)
{
	t_meta		*meta;
	t_env_node	*node;
	meta = get_meta();
	node = meta->env.tail;
	while (node)
	{
		printf("Key: %s  ", node->key);
		printf("Key len: %d\t", node->key_len);
		printf("Value: %s  ", node->value);
		printf("Value Len: %d\n", node->value_len);
		node = node->prev;
	}
}

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
		printf("[");
			while (*token->args_2d)
			{
				printf("%s, ", *token->args_2d);
				token->args_2d++;
			}
			printf("]");
		printf("-------------\n");
		free(type_buff);
		token = token->left;
	}
}

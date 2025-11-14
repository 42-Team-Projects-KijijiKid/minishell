#include "../../../inc/minishell.h"

static void	print_token_type(t_token *token)
{
	if (!token)
		ft_error("Error", __FILE__, __LINE__, 123);
	printf("type: ");
	if (token->type == PIPE)
		printf("\"|\"");
	else if (token->type == LPAREN)
		printf("\"(\"");
	else if (token->type == RPAREN)
		printf("\")\"");
	else if (token->type == AND_IF)
		printf("\"&&\"");
	else if (token->type == OR_IF)
		printf("\"||\"");
	else if (token->type == LESS)
		printf("\"<\"");
	else if (token->type == GREAT)
		printf("\">\"");
	else if (token->type == DGREAT)
		printf("\">>\"");
	else if (token->type == DLESS)
		printf("\"<<\"");
	else if (token->type == TEXT)
		printf("TEXT");
	else
		printf("<unknown type>");
}

static void	print_token_arguments(t_token *token)
{
	char	**strs;
	int		i;

	if (token && token->args && token->args[0])
	{
		strs = token->args;
		i = 0;
		printf("~ args: ");
		while (strs[i])
			printf("\"%s\", ", strs[i++]);	
		printf(" ~");
	}
}

static void	print_token(t_token *token)
{
	printf("	-  ");
	print_token_type(token);
	printf(", ");
	print_token_arguments(token);
	printf(";");
}

void	print_tokens(t_token *token, char *list_name)
{
	printf("Tokenlist %s:\n[\n", list_name);
	while (token)
	{
		print_token(token);
		printf("\n");
		token = token->next;
	}
	printf("]\n");
}

#include "parsing.h"

void	expand_tokens(t_token *head)
{
	if (!head)
		return ;
	if (*head->value == '$')
	{
		(head->value++);
		head->value = getenv((head->value));
	}
	expand_tokens(head->left);
	expand_tokens(head->right);
}

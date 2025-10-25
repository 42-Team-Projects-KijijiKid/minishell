#include "parsing.h"

void	expand_tokens(t_token *head, t_meta *meta)
{
	if (!head)
		return ;
	if (*head->value == '$')
	{
		(head->value++);
		head->value = getenv((head->value));
	}
	expand_tokens(head->left, meta);
	expand_tokens(head->right, meta);
}

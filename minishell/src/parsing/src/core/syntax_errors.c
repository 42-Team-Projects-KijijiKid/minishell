#include "parsing.h"

/// @brief Recursively goes trough the ast and 
/// checks for unclosed quotes or similar
/// @param head 
/// @param meta 
/// @return 
static int quote_err(t_token *head, int tmp_quote)
{
	if (!head)
		return (tmp_quote);
	if (*head->value == '"' || *head->value == '\'')
		tmp_quote++;
	tmp_quote =	quote_err(head->left, tmp_quote);
	return (quote_err(head->right, tmp_quote));
}

void	check_syntax(t_token *head)
{
	int	amount_qoutes;

	amount_qoutes = quote_err(head, 0);
	if (amount_qoutes % 2)
	{
			write(2, "Syntax Error:\n", 14);
			exit(1);
	}
}
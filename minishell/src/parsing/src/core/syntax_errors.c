#include "parsing.h"

/// @brief Recursively goes trough the ast and 
/// checks for unclosed quotes or similar
/// @param head 
/// @param meta 
/// @return 
t_token *syntax_errors(t_token *head, t_meta *meta, int quote_counter)
{
	if (!head)
		return (NULL);
	printf("%s\n", head->value);
	if (*head->value == '"' || *head->value == '\'')
		quote_counter++;
	syntax_errors(head->left, meta, quote_counter);
	syntax_errors(head->right, meta, quote_counter);
	if (quote_counter % 2)
	{
		write(2, "Syntax Error:\n", 14);
		exit(1);
	}
	return (NULL);
}

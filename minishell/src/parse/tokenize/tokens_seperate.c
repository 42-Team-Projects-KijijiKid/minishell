#include "../../../inc/minishell.h"

bool	is_meta_char(char cmd)
{
	int			i;
	const char	meta[11] = {'|', '&', ';', '(', ')',\
		'<', '>', '\\', '*', '?', '\0'};

	i = 0;
	if (!cmd)
		return (false);
	while (meta[i] && cmd != meta[i])
		i++;
	if (meta[i])
		return (true);
	return (false);
}

/// @brief Creating a simple linked list for
/// provided input devides between text and 
/// meta chars (inverted order)
/// @return pointer to the first elem(last command)
t_token	*tokens_seperate(char *input)
{
	t_token	*node;
	t_token	*head;

	head = NULL;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		node = (t_token *)fti_malloc(sizeof(t_token), TEMPORARY);
		node->prev = NULL;
		if (head)
			head->prev = node;
		node->args = NULL;
		node->next = head;
		if (is_meta_char(*input))
			node->args = tokenize_operator(&input);
		else
			node->args = tokenize_command(&input);
		head = node;
	}
	while (head->next)
		head = head->next;
	return (head);
}

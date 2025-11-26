#include "../../../inc/minishell.h"

static bool is_meta(char *str)
{
	char	match;

	if (*str != '&')
		return (true);
	match = *str;
	str++;
	if (!str)
		return (false);
	if (match == *str)
		return (true);
	return (false);
}

static void	assign_token_values(t_token *node, char **input)
{
	node->type = TEXT;
	node->args = NULL;
	if (is_meta_char(**input) && is_meta(*input))
	{
		node->type = evaluate_token_type(input);
		node->args = NULL;
	}
	else
		node->args = tokens_split_args(input);
}

static bool	skip_spaces(t_token *head, t_token *node, char **input)
{
	while (**input == ' ')
		(*input)++;
	if (!(**input))
	{
		if (head == node)
			*get_error_code() = 127;
		return (true);
	}
	return (false);
}

/// @brief Creating a simple linked list for
/// provided input devides between text and 
/// meta chars (inverted order)
/// @return pointer to the first elem(last command)
t_token	*tokenize(char *input)
{
	t_token	*node;
	t_token	*next;
	t_token	*head;

	node = (t_token *)fti_malloc(sizeof(t_token), TEMPORARY);
	head = node;
	node->prev = NULL;
	while (*input)
	{
		if (skip_spaces(head, node, &input))
			break ;
		assign_token_values(node, &input);
		if (!(*input))
			break ;
		if (*input == ';')
		{
			*get_error_code() = 127;
			return (NULL);
		}
		next = (t_token *)fti_malloc(sizeof(t_token), TEMPORARY);
		next->prev = node;
		node->next = next;
		node = next;
	}
	node->next = NULL;
	return (head);
}

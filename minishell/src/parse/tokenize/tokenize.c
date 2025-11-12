#include "../../../inc/minishell.h"

bool	is_meta_char(char input)
{
	int			i;
	const char	meta[11] = {'|', '&', ';', '(', ')',\
		'<', '>', '\\', '*', '?', '\0'};

	i = 0;
	if (!input)
		return (false);
	while (meta[i] && input != meta[i])
		i++;
	if (meta[i])
		return (true);
	return (false);
}

int	argument_length(char *input)
{
	int	i;

	i = 0;
	while (is_meta_char(input[i]))
		i++;
	return (i);
}

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
static e_tree_node_type	evaluate_token_type(char **input)
{
	int					len;
	e_tree_node_type	type;	

	len = argument_length(*input);
	if (ft_strncmp(input[0], "|", len) == 0)
		type = PIPE;
	else if (ft_strncmp(input[0], "(", len) == 0)
		type = LPAREN;
	else if (ft_strncmp(input[0], ")", len) == 0)
		type = RPAREN;
	else if (ft_strncmp(input[0], "&&", len) == 0)
		type = AND_IF;
	else if (ft_strncmp(input[0], "||", len) == 0)
		type = OR_IF;
	else if (ft_strncmp(input[0], "<", len) == 0)
		type = LESS;
	else if (ft_strncmp(input[0], ">", len) == 0)
		type = GREAT;
	else if (ft_strncmp(input[0], ">>", len) == 0)
		type = DGREAT;
	else if (ft_strncmp(input[0], "<<", len) == 0)
		type = DLESS;
	*input = *input + len;
	return (type);
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
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		node->type = TEXT;
		node->args = NULL;
		if (is_meta_char(*input))
		{
			node->type = evaluate_token_type(&input);
			node->args = NULL;
		}
		else
			node->args = tokens_split_args(&input);
		if (!(*input))
			break ;
		next = (t_token *)fti_malloc(sizeof(t_token), TEMPORARY);
		next->prev = node;
		node->next = next;
		node = next;
	}
	node->next = NULL;
	return (head);
}

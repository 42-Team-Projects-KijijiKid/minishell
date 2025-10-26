#include "parsing.h"

bool	is_meta_char(char cmd)
{
	int			i;
	const char	meta[14] = {'|', '&', ';', '(', ')',\
		'<', '>', '\"', '\'', '\\', '*', '?', '"', '\0'};

	i = 0;
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
t_tmp_cmd_token	*create_commands(char *cmd)
{
	t_tmp_cmd_token	*node;
	t_tmp_cmd_token	*head;
	t_meta *meta;

	meta = get_meta();
	head = NULL;
	while (*cmd)
	{
		ft_malloc(sizeof(t_tmp_cmd_token), LAYER_3);
		if (head)
			head->prev = node;
		node->args_2d = NULL;
		node->next = head;
		while (*cmd == ' ')
			cmd++;
		if (is_meta_char(*cmd))
		{
			//Could be qoutes or just operator
		}
		else
		{
			//Here we parse arguments 2D
		}
		head = node;
		node = node->next;
	}
	head->prev = NULL;
	while (head->next)
		head = head->next;
	return (head);
}

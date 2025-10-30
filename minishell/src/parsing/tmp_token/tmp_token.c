#include "parsing.h"

bool	is_meta_char(char cmd)
{
	int			i;
	const char	meta[14] = {'|', '&', ';', '(', ')',\
		'<', '>', '\"', '\'', '\\', '*', '?', '"', '\0'};

	i = 0;
	if (!cmd)
		return (false);
	while (meta[i] && cmd != meta[i])
		i++;
	if (meta[i])
		return (true);
	return (false);
}

char	**give_operator(char **str)
{
	char	**rtn;
	char	next_char;

	if (*(*str + sizeof(char)))
		next_char = *(*str + sizeof(char));
	rtn = ft_malloc(sizeof(char *) * 2, LAYER_2);
	if (is_meta_char(**str) && **str == next_char)
	{
		rtn[0] = ft_malloc((sizeof(char) * 2) + 1, LAYER_2);
		rtn[0][0] = **str;
		(*str)++;
		rtn[0][1] = **str;
		(*str)++;
		rtn[0][2] = '\0';
	}
	else
	{
		rtn[0] = ft_malloc((sizeof(char) * 1) + 1, LAYER_2);
		rtn[0][0] = **str;
		(*str)++;
		rtn[0][1] = '\0';
	}
	rtn[1] = NULL;
	return (rtn);
}

/// @brief Creating a simple linked list for
/// provided input devides between text and 
/// meta chars (inverted order)
/// @return pointer to the first elem(last command)
t_tmp_cmd_token	*create_commands(char *cmd)
{
	t_tmp_cmd_token	*node;
	t_tmp_cmd_token	*head;

	head = NULL;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (!*cmd)
			break ;
		node = ft_malloc(sizeof(t_tmp_cmd_token), LAYER_3);
		node->prev = NULL;
		if (head)
			head->prev = node;
		node->args_2d = NULL;
		node->next = head;
		if (is_meta_char(*cmd) && (*cmd != '\"' || *cmd != '\''))
			node->args_2d = give_operator(&cmd);
		else
			node->args_2d = special_split(&cmd);
		head = node;
	}
	while (head->next)
		head = head->next;
	return (head);
}

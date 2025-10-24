#include "parsing.h"

bool	is_meta_char(char cmd)
{
	int			i;
	const char	meta[15] = {'|', '&', ';', '(', ')',\
		'<', '>', '\"', '\'', '\\', '*', '$', '?', '"', '\0'};

	i = 0;
	while (meta[i] && cmd != meta[i])
		i++;
	if (meta[i])
		return (true);
	return (false);
}

char	*rtn_meta_str(char *cmd)
{
	int			i;
	char		*rtn;
	const char	meta[15] = {'|', '&', ';', '(', ')',\
		'<', '>', '\"', '\'', '\\', '*', '$', '?', '"', '\0'};

	i = 0;
	while (meta[i] && *cmd != meta[i])
		i++;
	if (meta[i] && meta[i] != cmd[1])
	{
		rtn = malloc(sizeof(char) + 1);
		rtn[0] = meta[i];
		rtn[1] = '\0';
		return (rtn);
	}
	else if (meta[i] && meta[i] == cmd[1])
	{
		rtn = malloc(sizeof(char) * 2 + 1);
		rtn[0] = meta[i];
		rtn[1] = meta[i];
		rtn[2] = '\0';
		return (rtn);
	}
	return (NULL);
}

char	*rtn_str(char *cmd)
{
	int		i;
	char	*rtn;

	i = 0;
	if (is_meta_char(*cmd))
		return (rtn_meta_str(cmd));
	while (cmd[i] && !is_meta_char(cmd[i])
		&& cmd[i] != ' ')
		i++;
	rtn = malloc(sizeof(char) * i + 1);
	i = 0;
	while (cmd[i] && !is_meta_char(cmd[i])
		&& cmd[i] != ' ')
	{
		rtn[i] = cmd[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char *get_and_advance_token(char **cmd_ptr)
{
	char	*rtn;

	rtn = NULL;
	if (is_meta_char(**cmd_ptr))
	{
		rtn = rtn_str(*cmd_ptr);
		(*cmd_ptr)++;
		if ((*rtn == '&' && *(rtn + 1) == '&')
			|| (*rtn == '|' && *(rtn + 1) == '|')
			|| (*rtn == '<' && *(rtn + 1) == '<')
			|| (*rtn == '>' && *(rtn + 1) == '>'))
			(*cmd_ptr)++;
	}
	else if (**cmd_ptr != ' ' && !is_meta_char(**cmd_ptr))
	{
		rtn = rtn_str(*cmd_ptr);
		while (**cmd_ptr && !is_meta_char(**cmd_ptr) && **cmd_ptr != ' ')
			(*cmd_ptr)++;
	}
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
		node = malloc(sizeof(t_tmp_cmd_token));
		if (head)
			head->prev = node;
		node->args_2d = NULL;
		node->value = NULL;
		node->next = head;
		while (*cmd == ' ')
			cmd++;
		if (!is_meta_char(*cmd))
			node->args_2d = special_split(&cmd);
		else
			node->value = get_and_advance_token(&cmd);
		head = node;
		node = node->next;
	}
	head->prev = NULL;
	while (head->next)
		head = head->next;
	return (head);
}

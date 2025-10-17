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

/// @brief Creating a simple linked list for
/// provided input devides between text and 
/// meta chars (inverted order)
/// @return pointer to the last head,
/// holding the last cmd in the string
t_tmp_cmd_token	*create_tokens(char *cmd)
{
	t_tmp_cmd_token	*node;
	t_tmp_cmd_token	*head;

	head = NULL;
	while (*cmd)
	{
		node = malloc(sizeof(t_tmp_cmd_token));
		node->next = head;
		while (*cmd == ' ')
			cmd++;
		if (is_meta_char(*cmd))
		{
			node->value = rtn_str(cmd);
			cmd++;
			if ((*node->value == '&' && *(node->value + 1) == '&')
				|| (*node->value == '|' && *(node->value + 1) == '|'))
				cmd++;
		}
		else if (*cmd != ' ' && !is_meta_char(*cmd))
		{
			node->value = rtn_str(cmd);
			while (*cmd && !is_meta_char(*cmd) && *cmd != ' ')
				cmd++;
		}
		head = node;
		node = node->next;
	}
	return (head);
}

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

static char	**give_operator(char **str)
{
	static char	*rtn[2];

	if (is_meta_char(**str) && is_meta_char(**str + 1))
	{
		rtn[0] = ft_malloc(sizeof(char) * 2, LAYER_2);
		rtn[0][0] = **str;
		(*str)++;
		rtn[0][1] = **str;
		(*str)++;
	}
	else
	{
		rtn[0] = ft_malloc(sizeof(char) * 1, LAYER_2);
		rtn[0][0] = *(*str)++;
	}
	rtn[1] = NULL;
	return (rtn);
}

static unsigned int	quoted_str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			break ;
		}
	}
	return (i + 1);
}

static char	**str_in_quotes(char **str)
{
	int			i;
	char 		**rtn;

	rtn	= ft_malloc(sizeof(char *) * 2, LAYER_2);
	i =  quoted_str_len(*str);
	rtn[0] = ft_malloc((sizeof(char) * i) + 1, LAYER_2);
	i = 0;
	rtn[0][i] = **str;
	(*str)++;
	while (**str != '\'' && **str != '\"')
	{
		i++;
		rtn[0][i] = **str;
		(*str)++;
	}
	i++;
	rtn[0][i] = **str;
	(*str)++;
	i++;
	rtn[0][i] = '\0';
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
	t_meta *meta;

	meta = get_meta();
	head = NULL;
	while (*cmd)
	{
		node = ft_malloc(sizeof(t_tmp_cmd_token), LAYER_3);
		if (head)
			head->prev = node;
		node->args_2d = NULL;
		node->next = head;
		while (*cmd == ' ')
			cmd++;
		if (is_meta_char(*cmd))
		{
			if (*cmd == '\"' || *cmd == '\'')
				node->args_2d = str_in_quotes(&cmd);
			else
				node->args_2d = give_operator(&cmd);
		}
		else
			node->args_2d = special_split(&cmd);
		head = node;
		node = node->next;
	}
	head->prev = NULL;
	while (head->next)
		head = head->next;
	return (head);
}

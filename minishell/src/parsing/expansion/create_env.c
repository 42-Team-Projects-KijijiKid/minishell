#include "parsing.h"

/// @brief Parses the env variables into
/// an 2D array
/// @param  
void	parse_env(char **envp)
{
	t_meta		*meta;
	t_env_node	*node;
	t_env_node	*head;

	meta = get_meta();
	head = NULL;
	while (*envp)
	{
		node = ft_malloc(sizeof(t_env_node), LAYER_2);
		if (head)
			head->prev = node;
		else
			meta->env.tail = node;
		node->next = head;
		node->key = abstract_key(envp);
		node->value = abstract_value(envp);
		node->key_len = ft_strlen(node->key);
		node->value_len = ft_strlen(node->value);
		envp++;
		head = node;
		meta->env.size++;
	}
	meta->env.head = head;
	// print_env();
	head->prev = NULL;
	char **test = turn_2d();
	print_2d_env(test);
}

/// @brief This is kinda like stringjoin
/// just takes the key and the value and
/// glues them togther, seperated by an
/// equal sign
/// @param node key and value node
/// @return 
char	*rtn_key_value(t_env_node *node)
{
	int		len;
	char	*rtn;
	int		i;

	len = node->value_len + node->key_len + EQUAL_SIGN;
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_1);
	i = 0;
	while (node->key[i])
	{
		rtn[i] = node->key[i];
		i++;
	}
	rtn[i++] = '=';
	while (*node->value)
	{
		rtn[i] = *node->value++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief This function turns the
/// env linked list in 2D array for
/// execeve
/// @param  
/// @return 2D array of env variables 
char	**turn_2d(void)
{
	t_meta		*meta;
	t_env_node	*node;
	char		**rtn;
	int			i;
	
	meta = get_meta();
	rtn = ft_malloc(sizeof(char *) * (meta->env.size + 1), LAYER_1);
	node = meta->env.tail;
	i = 0;
	while (node)
	{
		rtn[i] = rtn_key_value(node);
		node = node->prev;
		i++; 
	}
	rtn[i] = NULL;
	return (rtn);
}

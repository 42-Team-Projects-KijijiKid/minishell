#include "parsing.h"

/// @brief return the len to the
/// equal sign 
/// @param str 
/// @return length of cahrs till equal sign
unsigned int	len_to_equal(char *str)
{
	unsigned int	i;

	i = 0;
	while (*str != '=')
	{
		str++;
		i++;
	}
	return (i);
}

/// @brief Asbtarcts the value of env var
/// @param str 
/// @return NULL terminated value 
/// without the equal sign
static char	*abstract_value(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = ft_strlen(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_1);
	i = 0;
	while (**str)
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Abstracts the key of env var
/// Skips away the equal sign so
/// abstract_value can begin copy directly
/// @param str 
/// @return NULL terminated key
/// without the equal sign
static char	*abstract_key(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = len_to_equal(*str);
	rtn = ft_malloc(sizeof(char) * (len + 1), LAYER_1);
	i = 0;
	while (**str != '=')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	if (**str == '=')
		(*str)++;
	rtn[i] = '\0';
	return (rtn);
}

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
		printf("Key: %s\t", node->key);
		node->value = abstract_value(envp);
		printf("Value: %s\n", node->value);
		node->key_len = ft_strlen(node->key);
		node->value_len = ft_strlen(node->value);
		envp++;
		head = node;
		meta->env.size++;
	}
	head->prev = NULL;
}

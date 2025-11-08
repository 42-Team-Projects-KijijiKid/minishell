#include "parsing.h"

/// @brief Does not expand the variable
/// and removes the single quotes leaving the
/// inner quotes if present
/// @param str 
char	*single_quotes(char *str)
{
	int		str_len;
	char	*rtn;
	int		i;

	if (*str == '\'')
		str++;
	str_len = strlen_whitout_quotes(str, '\'');
	rtn = ft_malloc(sizeof(char) * str_len + 1, LAYER_2);
	i = 0;
	while (*str != '\'')
	{
		rtn[i] = *str;
		str++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Does not expand the variable
/// and removes the single quotes leaving the
/// inner quotes if present.
/// Rebuilds the whole string with expansion.
/// @param str 
char	*double_quotes(char *str)
{
	if (*str == '\"')
		str++;
	else
		ft_error("Tried to expand a invalid string", __FILE__, __LINE__, 73);
	return (expand_inside_str(str, '\"'));
}

/// @brief Directly expands the provided var
/// @param str 
/// @return 
char	*simple_expand(char *str)
{
	char	*rtn;
	char	*tmp_str;
	int		len;

	if (*str == '$')
		str++;
	else
		ft_error("Tried to expand a invalid string", __FILE__, __LINE__, 73);
	// tmp_str = rtn_env_value(str);
	if (!tmp_str)
		return (NULL);
	rtn = ft_strdup(tmp_str);	
	return (rtn);
}

/// @brief Goes trough 2D Array checking
///possible expansions and replacing the strings
void	possible_expansion(t_token *token)
{
	char **head;

	head = token->args_2d;
	while (*token->args_2d)
	{
		if (**token->args_2d == '\'')
			*token->args_2d = single_quotes(*token->args_2d);
		else if (**token->args_2d == '\"')
			*token->args_2d = double_quotes(*token->args_2d);
		else if (**token->args_2d == '$')
			*token->args_2d = simple_expand(*token->args_2d);
		token->args_2d++;
	}
	token->args_2d = head;
}

/// @brief Goes recursively through the binary tree
/// @param token 
void	expand_process(t_token *token)
{
	if (!token)
		return ;
	if (token->type == TEXT)
	{
		if (*token->args_2d && token->args_2d[1])
			possible_expansion(token);
	}
	expand_process(token->left);
	expand_process(token->right);
}

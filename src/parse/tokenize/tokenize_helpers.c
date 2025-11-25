#include "minishell.h"

bool	is_meta_char(char input)
{
	int			i;
	const char	meta[8] = {'|', '&', ';', '(', ')',\
		'<', '>', '\0'};

	i = 0;
	if (!input)
		return (false);
	while (meta[i] && input != meta[i])
		i++;
	if (meta[i])
		return (true);
	return (false);
}

static int	len_to_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
e_tree_node_type	evaluate_token_type(char **input)
{
	int					len;
	e_tree_node_type	type;	

	if (ft_strncmp(input[0], "&&", len = 2) == 0)
		type = AND_IF;
	else if (ft_strncmp(input[0], "||", len = 2) == 0)
		type = OR_IF;
	else if (ft_strncmp(input[0], ">>", len = 2) == 0)
		type = DGREAT;
	else if (ft_strncmp(input[0], "<<", len = 2) == 0)
		type = DLESS;
	else if (ft_strncmp(input[0], "|", len = 1) == 0)
		type = PIPE;
	else if (ft_strncmp(input[0], "(", len = 1) == 0)
		type = LPAREN;
	else if (ft_strncmp(input[0], ")", len = 1) == 0)
		type = RPAREN;
	else if (ft_strncmp(input[0], "<", len = 1) == 0)
		type = LESS;
	else if (ft_strncmp(input[0], ">", len = 1) == 0)
		type = GREAT;
	else if (!(len = 0))
		type = TEXT;
	*input = *input + len;
	return (type);
}

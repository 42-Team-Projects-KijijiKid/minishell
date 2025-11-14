#include "../../../inc/minishell.h"

/// @brief This function skips
/// every space and moves
/// the pointer pointer
static void	skip_space(char **input)
{
	while (**input && **input == ' ')
		(*input)++;
}

/// @brief Counts the leght of a single input
/// delimited by meta chars space or asterix(-)
/// @param input 
/// @return len of input
static int	len_of_input(char *input)
{
	int	i;

	i = 0;
	while (*input && !is_meta_char(*input)
			&& *input != ' '
			&& *input != '\''
			&& *input != '\"')
	{
		i++;
		input++;
	}
	return (i);
}

static char	*input_without_quotes(char **input)
{
	int		i;
	int		len;
	char	*rtn;

	len = len_of_input(*input);
	rtn = fti_malloc(sizeof(char) * (len + 1), TEMPORARY);
	i = 0;
	while (**input && !is_meta_char(**input)
			&& **input != ' ' && **input != '\''
			&& **input != '\"')
	{
		rtn[i] = **input;
		(*input)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

static char	*get_argument(char **input)
{
	while (**input)
	{
		skip_space(input);
		if (**input == '\'' || **input == '\"')
			return (input_in_quotes(input));
		else
			return (input_without_quotes(input));
	}
	return (NULL);
}

/// @brief This function creates 2D array with 
/// till end of provided command or if an operator
/// is reached. Handles also the quote rules checking
/// for quotes without content therefore earasing them.
/// Does not handle expansion!
/// @param input Command
/// @return A split up 2D array with applied 
/// bash rules for quotes till end or 
/// an operator is reached
char	**tokens_split_args(char **input)
{
	int		i;
	char	**rtn;
	int		words;

	words = count_arguments(*input);
	rtn = fti_malloc(sizeof(char *) * (words + 1), TEMPORARY);
	i = 0;
	while (i < words)
	{
		rtn[i] = get_argument(input);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

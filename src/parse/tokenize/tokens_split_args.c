#include "../../../inc/minishell.h"

static int	len_in_quotes(char *input)
{
	int		len;
	char	quote;

	quote = *input;
	input++;
	len = 1;
	while (quote != *input)
	{
		input++;
		len++;
	}
	if (*input == quote)
		len++;
	return (len);
}

unsigned int	total_len(char	*input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != ' ')
	{
		if (input[i] == '\''
			|| input[i] == '\"')
			i += len_in_quotes(&input[i]);
		else
			i++;
	}
	return (i);
}

static void	handle_quotes(char *rtn, int *i, char **input)
{
	char	quote;

	quote = **input;
	rtn[(*i)] = **input;
	(*i)++;
	(*input)++;
	while (**input != quote)
	{
		rtn[(*i)] = **input;
		(*i)++;
		(*input)++;
	}
}

static char	*get_argument(char **input)
{
	int		token_len;
	char	*rtn;
	int		i;

	i = 0;
	token_len = total_len(*input);
	rtn = fti_malloc(sizeof(char) * (token_len + 1), TEMPORARY);
	while (**input && **input != ' '
		&& !is_meta_char(**input))
	{
		if (**input == '\''
			|| **input == '\"')
		{
			handle_quotes(rtn, &i, input);
		}
		rtn[i] = **input;
		i++;
		(*input)++;
	}
	rtn[i] = '\0';
	return (rtn);
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
		while (**input
			&& **input == ' ')
			(*input)++;
		if (**input != '&')
			rtn[i] = get_argument(input);
		else
		{
			rtn[i] = fti_strdup("&", TEMPORARY);
			(*input)++;
		}
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

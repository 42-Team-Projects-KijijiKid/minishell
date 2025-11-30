/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:51 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:52 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_meta_char(char input)
{
	int			i;
	const char	meta[8] = {'|', '&', ';', '(', ')',
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

static void	single_char_evaluation(char **input, int *len,
			t_tree_node_type *type)
{
	*len = 1;
	if (ft_strncmp(input[0], "|", *len) == 0)
		*type = PIPE;
	else if (ft_strncmp(input[0], "(", *len) == 0)
		*type = LPAREN;
	else if (ft_strncmp(input[0], ")", *len) == 0)
		*type = RPAREN;
	else if (ft_strncmp(input[0], "<", *len) == 0)
		*type = LESS;
	else if (ft_strncmp(input[0], ">", *len) == 0)
		*type = GREAT;
	else
		*len = 0;
}

/// @brief Checks the cmd-> value for matches with strncmp
/// @param cmd tmporary command token
/// @return enum with the matching type 
t_tree_node_type	evaluate_token_type(char **input)
{
	int					len;
	t_tree_node_type	type;	

	len = 2;
	type = TEXT;
	if (ft_strncmp(input[0], "&&", len) == 0)
		type = AND_IF;
	else if (ft_strncmp(input[0], "||", len) == 0)
		type = OR_IF;
	else if (ft_strncmp(input[0], ">>", len) == 0)
		type = DGREAT;
	else if (ft_strncmp(input[0], "<<", len) == 0)
		type = DLESS;
	if (type == TEXT)
		single_char_evaluation(input, &len, &type);
	*input = *input + len;
	return (type);
}

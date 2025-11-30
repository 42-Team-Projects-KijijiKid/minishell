/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:57 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:59 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	find_matching_quote(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (**str && **str == quote)
	{
		(*str)++;
		return (true);
	}
	return (false);
}

/// @brief This checking for syntax errors.
/// Uneven amount of quotes. But impotant are also
/// cases like "'" because this is a valid expression
/// the check_withing functions handle thesee cases.
/// @param line 
void	validate_quote_pairs(char *line)
{
	int				*error_code;

	error_code = get_error_code();
	while (*line)
	{
		if (*line == '\'')
		{
			if (!find_matching_quote(&line))
				*error_code = print_error(
						"Syntax Error: wrong use of single quotes", 2);
		}
		else if (*line == '\"')
		{
			if (!find_matching_quote(&line))
				*error_code = print_error(
						"Syntax Error: wrong use of double quotes", 2);
		}
		if (*line && *line != '\''
			&& *line != '\"')
			line++;
	}
}

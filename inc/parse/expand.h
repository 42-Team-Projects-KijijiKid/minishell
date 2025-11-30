/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:18:13 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:18:14 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../structs.h"

// expand.c
t_tree_node		*expand(t_tree_node *node);

// expand_2.c
void			expand_arguments(t_tree_node *node);
char			*expand_single_argument(char *str);

// expand_helpers.c
bool			is_whitespace(char ch);
bool			check_char(char *str);
bool			env_value(char **str, char *rtn, int *i);
bool			quote_has_content(char *str);

// expand_helpers_2.c
char			*give_env_str(char **str);

// expand_total_len.c
unsigned int	total_length(char *str);

// get_environment_value.c
char			*get_environment_value(char *str);

#endif
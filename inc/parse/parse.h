/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:18:11 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:18:12 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "tokenize.h"
# include "expand.h"
# include "tree.h"

// parse.c
int		minishell_parse(char *input);
int		*get_error_code(void);

// parsing_validate.c
void	validate_quote_pairs(char *line);

// debug/print_tree.c
void	print_ast_structure(t_tree_node *root, int level, bool left);

// debug/debug_ast.c
void	debug_ast(char *prefix, char *file, int line, t_tree_node *node);
void	print_tokens(t_token *token, char *list_name);
int		*get_level(void);

#endif

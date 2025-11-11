#ifndef PARSE_H
# define PARSE_H

# include "tokenize.h"
# include "expand.h"
# include "tree.h"

// parse.c
void	minishell_parse(char *input);

// parsing_validate.c
void	validate_quote_pairs(char *line);

// debug/print_tree.c
void	print_ast_structure(t_tree_node *root, int level, bool left);

#endif

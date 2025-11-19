#ifndef PARSE_H
# define PARSE_H

# include "tokenize.h"
# include "expand.h"
# include "tree.h"

// parse.c
int	minishell_parse(char *input);

// parsing_validate.c
int	validate_quote_pairs(char *line);

// debug/print_tree.c
void	print_ast_structure(t_tree_node *root, int level, bool left);

// debug/debug_ast.c
void	debug_ast(char *prefix ,char *file, int line, t_tree_node *node);
void	print_tokens(t_token *token, char *list_name);
int		*get_level();

#endif

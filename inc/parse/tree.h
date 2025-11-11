#ifndef TREE_H
# define TREE_H

# include "../structs.h"

// tree_build_utils.c
t_tree_node	*token_to_tree_node(t_token *head_token);
void		remove_outer_parentheses(t_token **head_token);

// tree_build.c
void	tree_build(t_build_manager *manager);

// tree_find_root.c
t_token	*find_root(t_token *head_token);

// tree_redirect.c
void	build_redirect_chain(t_build_manager *manager, t_token *cmd);
void	build_redirection_tree(t_build_manager *manager);

#endif

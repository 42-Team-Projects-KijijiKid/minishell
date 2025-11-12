#ifndef TREE_H
# define TREE_H

# include "../structs.h"

// tree_build.c
void    	tree_build(t_build_manager *manager);

// tree_utils.c
t_tree_node	*token_to_tree_node(t_token *head_token);

// tree_redirects.c
void	    tree_redirects(t_build_manager *manager);

// tree_subshell.c
void		tree_subshells(t_build_manager *manager);

#endif

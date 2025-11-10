#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "../structs.h"

// redirect_append.c
int execute_rdr_append(t_tree_node *node);

// redirect_heredoc.c
int execute_rdr_heredoc(t_tree_node *node);

// redirect_in.c
int execute_rdr_in(t_tree_node *node);

// redirect_out.c
int execute_rdr_out(t_tree_node *node);

// redirection_utils.c
char	*get_redirect_filename(t_tree_node *node);
int		get_redirect_fd(t_tree_node *node);

#endif

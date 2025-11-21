#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "../structs.h"

// redirect_append.c
void	execute_rdr_append(t_redirect_node *redirect);

// redirect_heredoc.c
void	execute_rdr_heredoc(t_redirect_node *redirect);

// redirect_in.c
int		execute_rdr_in(t_redirect_node *redirect);

// redirect_out.c
void	execute_rdr_out(t_redirect_node *redirect);

#endif

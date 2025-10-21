#ifndef GARBAGE_H
# define GARBAGE_H

#include "minishell.h"

typedef struct	s_mem_block
{
	void	*mem;
	size_t	size;
	struct	s_mem_block;
}	t_mem_block;

t_mem_block	*add_to_layer(t_mem_block *layer, void *data);
void		free_layer(t_mem_block *layer_head);

#endif
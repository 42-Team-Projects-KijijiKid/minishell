#ifndef GARBAGE_H
# define GARBAGE_H

#include "minishell.h"

typedef enum	e_layer
{
	LAYER_1,
	LAYER_2,
	LAYER_3
}	t_layer_type;

typedef struct	s_mem_block
{
	struct	s_mem_block	*next;
	void				*mem;
}	t_mem_node;

typedef struct	s_layer
{
	t_mem_node	*head;
	t_mem_node	*tail;
	ssize_t		size;
}	t_layer;

typedef struct s_garbage
{
	t_layer	layer_1;
	t_layer	layer_2;
	t_layer	layer_3;
}	t_garbage;


void 		add_to_layer(t_layer *layer_meta, void *data);
void		free_layer(t_layer *layer_meta);
void		free_gc(void);

#endif
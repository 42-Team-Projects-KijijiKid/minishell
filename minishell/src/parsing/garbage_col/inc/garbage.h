#ifndef GARBAGE_H
# define GARBAGE_H

#include "minishell.h"

typedef struct	s_mem_node
{
	struct	s_mem_node	*next;
	void				*mem;
}	t_mem_node;

typedef struct	s_gc_layer
{
	struct s_mem_node	*head;
	struct s_mem_node	*tail;
	ssize_t				size;
} t_meta_layer;

typedef struct	s_garbage
{
	t_meta_layer			layer_1;
	t_meta_layer			layer_2;
	t_meta_layer			layer_3;
}	t_garbage;


t_mem_node	*add_to_layer(t_mem_node *layer, void *data);
void		free_layer(t_mem_node *layer_head);


// BEGIN -- Cloud Meta

// END -- Cloud Meta

#endif
#include "../../inc/minishell.h"

void	garbage_add_node(t_garbage_layer *layer_meta, void *data)
{
	t_garbage_node	*node;
	
	node = malloc(sizeof(t_garbage_node));
	if (!node)
		ft_error("Malloc failed", __FILE__, __LINE__, 2);
	if (layer_meta->size == 0)
	{
		node->next = NULL;
		node->mem = data;
		layer_meta->head = node;
		layer_meta->tail = node;
		layer_meta->size++;
	}
	else
	{
		node->next = layer_meta->head;
		node->mem = data;
		layer_meta->head = node;
		layer_meta->size++;
	}
}

/// @brief Adds the provided data to a linked list.
/// @param layer_head Layer where to add the data.
/// @param data void pointer of the data
/// @return new head of layer
void garbage_add_to_layer(t_garbage_layer *layer_meta, void *data)
{
	garbage_add_node(layer_meta, data);
}

/// @brief Totaly frees the stored information of the layer
/// @param layer_head Provided layer
void	garbage_free_layer(t_garbage_layer *layer_meta)
{
	t_garbage_node 	*tmp;

	while (layer_meta->head)
	{
		tmp = layer_meta->head;
		layer_meta->head = layer_meta->head->next;
		free(tmp->mem);
		free(tmp);
	}
}

/// @brief Frees entire layers of
/// the garbage collector
/// @param  
void	garbage_free_all(void)
{
	t_minishell	*meta;

	meta = minishell_get();
	clear_history();
	garbage_free_layer(&meta->garbage.persistent);
	garbage_free_layer(&meta->garbage.temporary);
}

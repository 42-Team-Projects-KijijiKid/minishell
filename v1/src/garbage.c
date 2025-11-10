#include "../inc/minishell.h"

void	garbage_add_node(t_garbage_layer *garbage_layer, void *data)
{
	t_garbage_node	*node;
	
	node = malloc(sizeof(t_garbage_node));
	if (!node)
		ft_error("Malloc failed", __FILE__, __LINE__, 2);
	if (garbage_layer->size == 0)
	{
		node->next = NULL;
		node->mem = data;
		garbage_layer->head = node;
		garbage_layer->tail = node;
		garbage_layer->size++;
	}
	else
	{
		node->next = garbage_layer->head;
		node->mem = data;
		garbage_layer->head = node;
		garbage_layer->size++;
	}
}

/// @brief Adds the provided data to a linked list.
/// @param layer_head Layer where to add the data.
/// @param data void pointer of the data
/// @return new head of layer
void garbage_add_to_layer(t_garbage_layer *garbage_layer, void *data)
{
	garbage_add_node(garbage_layer, data);
}

/// @brief Totaly frees the stored information of the layer
/// @param layer_head Provided layer
void	garbage_free_layer(t_garbage_layer *garbage_layer)
{
	t_garbage_node 	*tmp;

	while (garbage_layer->head)
	{
		tmp = garbage_layer->head;
		garbage_layer->head = garbage_layer->head->next;
		free(tmp->mem);
		free(tmp);
	}
}

/// @brief Frees entire layers of
/// the garbage collector
/// @param  
void	garbage_free_all(void)
{
	t_minishell	*shell;

	shell = minishell_get();
	garbage_free_layer(&shell->garbage.persistent);
	garbage_free_layer(&shell->garbage.temporary);
}

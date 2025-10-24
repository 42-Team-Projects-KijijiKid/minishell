#include "garbage.h"

static t_mem_block  *create_first_node(void *data)
{
    t_mem_block* first_node;

	first_node = malloc(sizeof(t_mem_block));
	first_node->mem = data;
}

/// @brief Adds the provided data to a linked list.
/// @param layer_head Layer where to add the data.
/// @param data void pointer of the data
/// @return new head of layer
t_mem_block	*add_to_layer(t_mem_block *layer_head, void *data)
{
	t_mem_block	*head;

	if (!data)
	{
		write(2, "No Data to add\n", 15);
		return ;
	}
	if (!layer_head)
        head = create_first_node(data);

    return (head);
}

/// @brief Totaly frees the stored information of the layer
/// @param layer_head Provided layer
void	free_layer(t_mem_block *layer_head)
{
	if (!layer_head)
	{
		write(2, "Nothing to free\n", 16);
		return ;
	}
}

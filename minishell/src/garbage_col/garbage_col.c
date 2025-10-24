#include "garbage.h"

static t_mem_block  *add_node(t_mem_block *head, void *data)
{
	t_mem_block	*tmp;

	tmp = malloc(sizeof(t_mem_block));
	if (!tmp)
	{
		write(2, "Malloc Failed", 13);
		exit (120);
	}
	tmp->mem = data;
	tmp->next = head;
	head = tmp;
	return (head);
}

static t_mem_block  *create_first_node(void *data)
{
    t_mem_block* first_node;

	first_node = malloc(sizeof(t_mem_block));
	if (!first_node)
	{
		write(2, "Malloc Failed", 13);
		exit (120);
	}
	first_node->mem = data;
	first_node->next = NULL;
	return (first_node);
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
		return (NULL);
	}
	if (!layer_head)
        head = create_first_node(data);
	else
		head = add_node(layer_head, data);
    return (head);
}

/// @brief Totaly frees the stored information of the layer
/// @param layer_head Provided layer
void	free_layer(t_mem_block *layer_head)
{
	t_mem_block	*tmp;

	if (!layer_head)
	{
		write(2, "Nothing to free\n", 16);
		return ;
	}
	while (layer_head)
	{
		tmp = layer_head;
		layer_head = layer_head->next;
		free(tmp->mem);
		free(tmp);
	}
}

int	main(void)
{
	int	i;
	char *test;
	t_mem_block	*layer_1;

	i = 0;
	while (i < 100)
	{
		test = malloc(1234);
		layer_1 = add_to_layer(layer_1, (void*)test);
		i++;
	}
	free_layer(layer_1);
}
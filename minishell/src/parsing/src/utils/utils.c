#include "minishell.h"

t_meta	*get_meta(void) 
{
	static t_meta	meta = {0};

	return (&meta);
}

t_meta	*init_meta(void) 
{
	t_meta *meta;

	meta = get_meta();
	meta->garbage.layer_1.head = NULL;
	meta->garbage.layer_1.tail = NULL;
	meta->garbage.layer_1.size = 0;
	meta->garbage.layer_2.head = NULL;
	meta->garbage.layer_2.tail = NULL;
	meta->garbage.layer_2.size = 0;


	///

	return (meta);
}
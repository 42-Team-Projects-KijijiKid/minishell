#include "../../inc/minishell.h"

void	*ft_malloc(ssize_t size, e_garbage_layers type)
{
	t_minishell	*meta;
	void	*rtn;

	meta = minishell_get();
	rtn = malloc(size);
	if (!rtn)
		ft_error("Malloc failed", __FILE__, __LINE__, 2);
	if (type == PERSISTENT)
		add_to_layer(&meta->garbage.persistent, (void *)rtn);
	else if (type == TEMPORARY)
		add_to_layer(&meta->garbage.temporary, (void *)rtn);
	else
		ft_error("Provided Layer does not exist", __FILE__, __LINE__, 12);
	return (rtn);
}

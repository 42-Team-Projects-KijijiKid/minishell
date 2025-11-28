#include "../../../inc/minishell.h"

void	*fti_malloc(ssize_t size, t_garbage_layers type)
{
	t_minishell	*meta;
	void		*rtn;

	meta = minishell_get();
	rtn = malloc(size);
	if (!rtn)
		ft_error("Malloc failed", __FILE__, __LINE__, 2);
	ft_bzero(rtn, size);
	if (type == PERSISTENT)
		garbage_add_to_layer(&meta->garbage.persistent, (void *)rtn);
	else if (type == TEMPORARY)
		garbage_add_to_layer(&meta->garbage.temporary, (void *)rtn);
	else
		ft_error("Provided Layer does not exist", __FILE__, __LINE__, 12);
	return (rtn);
}

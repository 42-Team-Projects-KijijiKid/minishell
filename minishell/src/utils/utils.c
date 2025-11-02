#include "minishell.h"

/// @brief Opens the file and handles error msg
/// @param filename 
/// @param oflag 
/// @return File descriptor on success
int ft_open(char *filename, int oflag)
{
	int	fd;

	fd = open(filename, oflag);
	if (fd = -1)
		ft_error("Open failed", __FILE__, __LINE__, 98);
	return (fd);
}


t_meta	*get_meta(void) 
{
	static t_meta	meta = {0};

	return (&meta);
}

t_meta	*init_meta(char **envp) 
{
	t_meta *meta;

	meta = get_meta();
	meta->garbage.layer_1.head = NULL;
	meta->garbage.layer_1.tail = NULL;
	meta->garbage.layer_1.size = 0;
	meta->garbage.layer_2.head = NULL;
	meta->garbage.layer_2.tail = NULL;
	meta->garbage.layer_2.size = 0;
	meta->garbage.layer_3.head = NULL;
	meta->garbage.layer_3.tail = NULL;
	meta->garbage.layer_3.size = 0;
	parse_env(envp);
	return (meta);
}

void	*ft_malloc(ssize_t size, t_layer_type type)
{
	t_meta	*meta;
	void	*rtn;

	meta = get_meta();
	rtn = malloc(size);
	if (!rtn)
		ft_error("Malloc failed", __FILE__, __LINE__, 2);
	if (type == LAYER_1)
		add_to_layer(&meta->garbage.layer_1, (void *)rtn);
	else if (type == LAYER_2)
		add_to_layer(&meta->garbage.layer_2, (void *)rtn);
	else if (type == LAYER_3)
		add_to_layer(&meta->garbage.layer_1, (void *)rtn);
	else
		ft_error("Provided Layer does not exist", __FILE__, __LINE__, 12);
	return (rtn);
}
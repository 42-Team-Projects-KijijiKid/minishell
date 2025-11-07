#include "parsing.h"



char	*ft_readline(char *promt)
{
	char	*cmd;
	t_meta	*meta;
	int		len;

	meta = get_meta();
	while (1)
	{
		cmd = readline(promt);
		if (!cmd)
			return (NULL);
		len = ft_strlen(cmd);
		if (len != 0)
		{
			if (ft_strncmp(cmd, "exit", len) == 0)
				return (NULL);
			return (cmd);
		}
		else
			continue ;
	}
}

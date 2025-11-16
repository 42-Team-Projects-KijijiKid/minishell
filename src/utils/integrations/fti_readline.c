#include "../../../inc/minishell.h"

char	*fti_readline(char *promt)
{
	char		*cmd;
	int			len;

	cmd = NULL;
	while (1)
	{
		cmd = readline(promt);
		if (!cmd)
			return (NULL);
		len = ft_strlen(cmd);
		if (len != 0)
		{
			if (ft_strncmp(cmd, "exit", len) == 0
				&& len == 4)
				return (NULL);
			add_history(cmd);
			return (cmd);
		}
		else
			continue ;
	}
}

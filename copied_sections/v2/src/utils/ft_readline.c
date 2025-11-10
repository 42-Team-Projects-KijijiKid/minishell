#include "../../inc/minishell.h"

char	*ft_readline(char *promt)
{
	char		*cmd;
	t_minishell	*shell;
	int			len;

	shell = minishell_get();
	while (1)
	{
		cmd = readline(promt);
		len = ft_strlen(cmd);
		if (!cmd)
			return (NULL);
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

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
		{
			printf("\n");
			return (NULL);
		}
		len = ft_strlen(cmd);
		if (len != 0)
		{
			add_history(cmd);
			return (cmd);
		}
		else
			continue ;
	}
}

#include "minishell.h"

/// @brief Goes through the environment variables,
/// searching for matching patterns
/// @param to_search Key to abstract the value from env
/// @return the value 
char	*rtn_env_value(char *to_search)
{
	t_meta	*meta;
	char	**envp;
	int		str_len;

	meta = get_meta();
	str_len = ft_strlen(to_search);
	while (*envp)
	{
		if (ft_strncmp(to_search, *envp, str_len) == 0)
		{
			return (*envp + (sizeof(char) * str_len + 1));
		}
		envp++;
	}
	return (NULL);
}

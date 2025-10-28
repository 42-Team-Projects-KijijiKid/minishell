#include "minishell.h"

/// @brief Goes through the environment variables,
/// searching for matching patterns
/// @param to_search Null terminated string to 
/// abstract the value from env,
/// @return the value 
char	*rtn_env_value(char *to_search)
{
	t_meta	*meta;
	char	**envp;
	int		str_len;
	char	*a;

	if (!to_search)
		ft_error("No to_search provided", __FILE__, __LINE__, 93);
	meta = get_meta();
	envp = meta->envp;
	str_len = ft_strlen(to_search);
	while (*envp)
	{
		a = *envp;
		if (ft_strncmp(to_search, *envp, str_len) == 0)
			return (*envp + (sizeof(char) * str_len + 1));
		envp++;
	}
	return (NULL);
}

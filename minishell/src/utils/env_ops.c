// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/// @brief Goes through the environment variables,
/// searching for matching patterns
/// @param to_search Key to abstract the value from env
/// @return the value 
char	*rtn_env_value(char *to_search, char **envp)
{
	// t_meta	*meta;
	// char	**envp;
	int		str_len;

	// meta = get_meta();
	// envp = meta->envp;
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

int	main(int ac, char **av, char **envp)
{
	printf("%s\n", rtn_env_value(av[1], envp));
}

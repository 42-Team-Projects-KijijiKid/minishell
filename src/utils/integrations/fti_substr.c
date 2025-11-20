#include "minishell.h"

char	*fti_substr(const char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (fti_strdup("", PERSISTENT));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = fti_malloc(sizeof(char) * (len + 1), PERSISTENT);
	if (!(substr))
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

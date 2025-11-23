# include "minishell.h"

char	*fti_strdup(const char *s, e_garbage_layers layer)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	if (s[1] == '/')
		return (fti_strdup("/", TEMPORARY));
	s_len = ft_strlen(s);
	ptr = fti_malloc(sizeof(char) * s_len + 1, layer);
	if (!(ptr))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
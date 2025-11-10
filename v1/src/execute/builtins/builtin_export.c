#include "../../../inc/minishell.h"

static char	*extract_key(const char *arg)
{
	size_t	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	char	*key = ft_substr(arg, 0, i); // New version required, that adds to garbage collector
	return (key);
}

static char	*extract_value(const char *arg)
{
	char	*eq = ft_strchr(arg, '='); // New version required?
	if (!eq)
		return (NULL);
	char	*value = ft_strdup(eq + 1); // New version required, that adds to garbage collector
	return (value);
}

static int	print_exported_vars(void)
{
	t_minishell	*shell;
	t_env_node	*node;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		if (printf("declare -x %s=\"%s\"\n", node->key, node->value) < 0)
			return (ft_error("printf failed", __FILE__, __LINE__, 932), 932);
		node = node->next;
	}
	return (0);
}

int builtin_export(char **args)
{
	if (!args || !args[0] || ft_strcmp(args[0], "export") != 0)
		return (ft_error("export: invalid arguments", __FILE__, __LINE__, 930), 930);
	if (!args[1])
		return (print_exported_vars());
	int i = 1;
	while (args[i])
	{
		char *key = extract_key(args[i]);
		char *value = extract_value(args[i]);
		if (key && ft_strlen(key) > 0)
		{
			if (value)
				env_set_value(key, value);
			else
				env_set_value(key, "");
		}
		else
			return (ft_error("export: invalid argument", __FILE__, __LINE__, 931), 931);
		i++;
	}
	return (0);
}

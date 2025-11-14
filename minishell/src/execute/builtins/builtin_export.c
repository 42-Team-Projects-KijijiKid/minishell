#include "../../../inc/minishell.h"

static char	*extract_key(const char *arg)
{
	char	*key;
	size_t	i;
	
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i); // New version required, that adds to garbage collector
	return (key);
}

static char	*extract_value(const char *arg)
{
	char	*eq;
	char	*value;

	eq = ft_strchr(arg, '='); // New version required?
	if (!eq)
		return (NULL);
	value = ft_strdup(eq + 1); // New version required, that adds to garbage collector
	return (value);
}

static void	print_exported_vars(void)
{
	t_minishell	*shell;
	t_env_node	*node;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		printf("declare -x %s=\"%s\"\n", node->key, node->value); // TODO: Question: Check for printf errors?
		node = node->next;
	}
}

int builtin_export(char **args)
{
	if (!args || !args[0] || ft_strncmp(args[0], "export", ft_strlen(*args)) != 0)
		ft_error("export: invalid arguments", __FILE__, __LINE__, 930);
	if (!args[1])
	{
		print_exported_vars();
		exit(0);
	}
	int i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') || args[i][0] == '=' || args[i][0] == '\0')
			ft_error("export: invalid argument", __FILE__, __LINE__, 931);
		char *key = extract_key(args[i]);
		char *value = extract_value(args[i]); // TODO: Question: expansion possible? already handled?
		if (value)
			env_set_value(key, value);
		else
			env_set_value(key, "");
		i++;
	}
	return (0);
}

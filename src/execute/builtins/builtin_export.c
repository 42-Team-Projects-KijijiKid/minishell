#include "../../../inc/minishell.h"

static char	*extract_key(const char *arg)
{
	char	*key;
	size_t	i;
	
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = fti_substr(arg, 0, i); // New version required, that adds to garbage collector
	return (key);
}

static char	*extract_value(const char *arg)
{
	char	*eq;
	char	*value;

	eq = ft_strchr(arg, '='); // New version required?
	if (!eq)
		return (NULL);
	value = fti_strdup(eq + 1, TEMPORARY); // New version required, that adds to garbage collector
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
		ft_fprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

static bool	validate_argument(char *str)
{
	bool	valid;
	char	*buf;

	if (ft_isdigit(*str))
	{
		ft_fprintf(2, "export: %s: not a valid identifier\n", str);
		return (false);
	}
	valid = true;
	while (*str != '=')
	{
		if (!ft_isalnum(*str)
			&& *str == ' ')
			valid = false;
		str++;
	}
	if (!valid)
		ft_fprintf(2, "export: %s: not a valid identifier\n", buf);
	return (valid);
}

int builtin_export(char **args)
{
	int i;

	if (!args[1])
		return (print_exported_vars());
	i = 1;
	while (args[i])
	{
		if (!validate_argument(args[i]))
			return (1);
		char *key = extract_key(args[i]);
		char *value = extract_value(args[i]); 
		if (value)
			env_set_value(key, value);
		else
			env_set_value(key, "");
		i++;
	}
	return (0);
}

#include "minishell.h"

static char	*heredoc_loop(const char *delim)
{
	char *line;
	char *full_input;

	full_input = ft_strdup(""); // New version required, that adds to garbage collector
	while (1)
	{
		line = ft_readline("> ");
		if (!line)
			break; 
		if (strcmp(line, delim) == 0)
		{
			free(line); // add_history(line); like in main?
			break;
		}
		full_input = ft_strjoin(full_input, line); // New version required, that adds to garbage collector
		full_input = ft_strjoin(full_input, "\n"); // New version required, that adds to garbage collector
		free(line); // add_history(line); like in main?
	}
	return (full_input);
}

static char	*expand_heredoc_input(char **input, char *delim)
{
	char *expanded;

	if (!input || !(*input))
		return (NULL);
	if (delim[0] == '\"' || delim[0] == '\'')
	{
		if (delim[ft_strlen(delim) - 1] == delim[0])
			return (*input);
		return (ft_error("Mismatched quotes in heredoc delimiter", \
			__FILE__, __LINE__, 0), NULL);
	}
	// expanded = expand_variables(*input); // add Mateos function
	return (expanded);
}

int execute_rdr_heredoc(t_tree_node *node)
{
	char *input;
	if (!node || node->type != DLESS)
		return (ft_error("Node is NULL or has incorrect type", \
			__FILE__, __LINE__, 950), 950);
	if (!(node->args) || !(node->args[0]) || ft_strlen(node->args[0]) == 0)
		return (ft_error("Heredoc delimiter is NULL or empty", \
			__FILE__, __LINE__, 951), 951);
	input = heredoc_loop(node->args[0]);
	if (!input)
		return (ft_error("Failed to read heredoc input", \
			__FILE__, __LINE__, 952), 952);
	input = expand_heredoc_input(&input, node->args[0]);
	if (!input)
		return (ft_error("Failed to expand heredoc input", \
			__FILE__, __LINE__, 953), 953);
	write(STDIN_FILENO, input, ft_strlen(input));
	return (0);
}

#include "minishell.h"

static char	*heredoc_loop(const char *delim)
{
	char *line;
	char *full_input;

	full_input = fti_strdup(""); // TODO: New version required, that adds to garbage collector
	while (1)
	{
		line = readline(">");
		if (!line)
			break; 
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line); // TODO: add_history(line); like in main?
			break;
		}
		full_input = fti_strjoin(full_input, line); // TODO: New version required, that adds to garbage collector
		full_input = fti_strjoin(full_input, "\n"); // TODO: New version required, that adds to garbage collector
		free(line); // TODO: add_history(line); like in main?
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
		ft_error("Mismatched quotes in heredoc delimiter", \
			__FILE__, __LINE__, 0);
	}
	// expanded = expand_variables(*input); // TODO: add Mateos function and check, if if-condition in line 53 after expand_heredoc_input still makes sense
	return (expanded);
}

void execute_rdr_heredoc(t_redirect_node *redirect)
{
	char *input;
	
	if (!(redirect->file) || ft_strlen(redirect->file) == 0) // TODO: Check, if heredoc writes delimiter in file attribute
		ft_error("Heredoc delimiter is NULL or empty", \
			__FILE__, __LINE__, 951);
	// input = heredoc_loop(redirect->args[0]);
	if (!input)
		ft_error("Failed to read heredoc input", \
			__FILE__, __LINE__, 952);
	// input = expand_heredoc_input(&input, redirect->args[0]);
	if (!input)
		ft_error("Failed to expand heredoc input", \
			__FILE__, __LINE__, 953);
	write(STDIN_FILENO, input, ft_strlen(input));
}

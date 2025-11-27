#include "minishell.h"

t_minishell	*minishell_get(void)
{
	static t_minishell	shell = {0};

	return (&shell);
}

t_minishell	*minishell_initialize(char **env)
{
	t_minishell	*shell;

	shell = minishell_get();
	shell->garbage.persistent.head = NULL;
	shell->garbage.persistent.tail = NULL;
	shell->garbage.persistent.size = 0;
	shell->garbage.temporary.head = NULL;
	shell->garbage.temporary.tail = NULL;
	shell->garbage.temporary.size = 0;
	shell->filedescriptor.std_in = dup(STDIN_FILENO);
	shell->filedescriptor.std_out = dup(STDOUT_FILENO);
	shell->filedescriptor.std_err = dup(STDERR_FILENO);
	shell->herdoc = true;
	shell->fd_table.head = NULL;
	shell->fd_table.tail = NULL;
	shell->fd_table.size = 0;
	environment_initialize(env);
	return (shell);
}

static bool	minishell_interactive(void)
{
	char		*cmd;
	t_minishell	*shell;
	int			*error_code;

	shell = minishell_get();
	error_code = get_error_code();
	*error_code = 0;
	shell->herdoc = true;
	cmd = fti_readline("Minishell>> ");
	if (!cmd)
		return (false);
	minishell_parse(cmd);
	if (*error_code == 0)
		minishell_execute();
	free(cmd);
	garbage_free_layer(&shell->garbage.temporary);
	return (true);
}

static bool	minishell_non_interactive(void)
{
	char		*cmd;
	t_minishell	*shell;
	int			*error_code;

	shell = minishell_get();
	error_code = get_error_code();
	*error_code = 0;
	shell->herdoc = true;
	cmd = read_next_line();
	if (!cmd || *cmd == '\0')
		return (false);
	minishell_parse(cmd);
	if (*error_code == 0)
		minishell_execute();
	garbage_free_layer(&shell->garbage.temporary);
	return (true);
}

void	minishell_run(void)
{
	while (isatty(STDIN_FILENO))
	{
		if (!minishell_interactive())
			break ;
	}
	while (!isatty(STDIN_FILENO))
	{
		if (!minishell_non_interactive())
			break ;
	}
}

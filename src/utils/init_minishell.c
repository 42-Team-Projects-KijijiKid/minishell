#include "minishell.h"

t_minishell	*minishell_get(void)
{
	static t_minishell	shell = {0};

	return (&shell);
}

t_minishell	*minishell_initialize(char **env)
{
	t_minishell *shell;

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
	environment_initialize(env);
	return (shell);
}

void	run_minishell(void)
{
	char		*cmd;
	t_minishell	*shell;

	shell = minishell_get();
	while (isatty(STDIN_FILENO))
	{
		shell->herdoc = true;
		cmd = fti_readline("\033[32mMinishell>>\033[0m ");
		if (!cmd)
			break ;
		minishell_parse(cmd);
		minishell_execute();
		free(cmd);
		garbage_free_all();
		exit (101);
	}
	while (!isatty(STDIN_FILENO))
	{
		cmd = get_next_line(STDIN_FILENO);
		if (!cmd)
			break ;
		minishell_parse(cmd);
		minishell_execute();
		free(cmd);
	}
	garbage_free_layer(&shell->garbage.persistent);
	printf("exit\n");
}

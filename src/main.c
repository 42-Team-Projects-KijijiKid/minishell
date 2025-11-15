#include "../inc/minishell.h"

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
	environment_initialize(env);
	return (shell);
}

int main(int ac, char **av, char **env)
{
	char		*cmd;
	t_minishell	*shell;

	(void)ac;
	(void)av;
	shell = minishell_initialize(env);
	while (isatty(fileno(stdin)))
	{
		cmd = fti_readline("\033[34mMinishell>>\033[0m ");
		if (!cmd)
			break ;
		minishell_parse(cmd);
		// ######### -- continue -->
		minishell_execute();
		garbage_free_layer(&shell->garbage.temporary);
	}
	while (!isatty(fileno(stdin)))
	{
		char	*line;
		line = get_next_line(fileno(stdin));
		if (!line)
			break ;
		minishell_parse(line);
		minishell_execute();
		free(line);
	}
	printf("\033[37;5mGoodbye!\033[0m\n");
	garbage_free_all();
}

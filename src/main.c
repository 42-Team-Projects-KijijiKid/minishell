#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
	t_minishell	*shell;
	char		*cmd;

	(void)ac;
	(void)av;
	sig_init();
	shell = minishell_initialize(env);
	run_minishell();
	clear_history();
	close_default_filedescriptor();
	garbage_free_layer(&shell->garbage.persistent);
	if (isatty(STDIN_FILENO))
		ft_fprintf(1, "exit\n");
	exit(shell->last_exit_status);
}

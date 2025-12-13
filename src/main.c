#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;

	(void)ac;
	(void)av;
	sig_init();
	shell = minishell_initialize(env);
	update_shell_level();
	minishell_run();
	clear_history();
	close_default_filedescriptor();
	garbage_free_all();
	if (isatty(STDIN_FILENO))
		ft_fprintf(1, "exit\n");
	close(shell->filedescriptor.std_err);
	close(shell->filedescriptor.std_in);
	close(shell->filedescriptor.std_out);
	exit(shell->last_exit_status);
}

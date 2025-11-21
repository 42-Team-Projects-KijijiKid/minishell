#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
	t_minishell			*shell;
	char				*cmd;

	(void)ac;
	(void)av;
	sig_init();
	shell = minishell_initialize(env);
	run_minishell();
	rl_clear_history();
	close(shell->filedescriptor.std_in);
	close(shell->filedescriptor.std_out);
	close(shell->filedescriptor.std_err);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	garbage_free_all();
}

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
	close_default_filedescriptor();
	garbage_free_all();
}

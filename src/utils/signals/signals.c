#include "minishell.h"

void	ctrl_c(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ctrl_heredoc(int sig)
{
	exit(100);
}

void	sig_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
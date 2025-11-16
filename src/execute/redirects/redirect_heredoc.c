#include "minishell.h"

void	run_child(char *limiter, int *pipe_fds)
{
	char	*line;

	close(pipe_fds[0]);
	while (1)
	{
		write(1, "here_doc> ", ft_strlen("here_doc> "));
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0
			&& *line != '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fds[1]);
	exit(0);
}

/// @brief Initializes a here_doc in a child process
/// @param limiter Limiter character
/// @return The read-end of the pipe the content of here_doc
/// was writting to
int	init_here_doc(char *limiter)
{
	int		pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		set_error(2);
	pid = fork();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 120);
	if (pid == 0)
		run_child(limiter, pipe_fds);
	else
		wait(NULL);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

void	execute_rdr_heredoc(t_redirect_node *redirect)
{
	int	pipe_read_end;

	pipe_read_end = init_here_doc(redirect->file);
	dup2(pipe_read_end, STDIN_FILENO);
}

#include "minishell.h"

static size_t	len_to_newline(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

static void	run_heredoc(char *delimiter, int *pipe_fds)
{
	char		*line;
	t_minishell	*shell;
	size_t		len;

	sig_heredoc();
	shell = minishell_get();
	add_fd_to_list(pipe_fds[1]);
	close(pipe_fds[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		garbage_add_to_layer(&shell->garbage.persistent, line);
		len = len_to_newline(line);
		if (ft_strncmp(line, delimiter, len) == 0
			&& *line != '\n' && len == ft_strlen(delimiter))
			break ;
		write(pipe_fds[1], line, len);
		write(pipe_fds[1], "\n", 1);
	}
	garbage_free_all();
	close_default_filedescriptor();
	close(pipe_fds[1]);
	exit(0);
}

/// @brief Initializes a here_doc in a child process
/// @param delimiter delimiter character
/// @return The read-end of the pipe the content of here_doc
/// was writting to
int	initialize_heredoc(char *delimiter)
{
	int			pid;
	int			pipe_fds[2];
	t_minishell	*shell;
	int			wstatus;

	shell = minishell_get();
	if (pipe(pipe_fds) == -1)
		ft_error(PIPE_FAILED, __FILE__, __LINE__, 131);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, __FILE__, __LINE__, 131);
	if (pid == 0)
		run_heredoc(delimiter, pipe_fds);
	if (waitpid(pid, &wstatus, 0) == -1
		|| wstatus != 0)
	{
		shell->last_exit_status = 130;
		close(pipe_fds[0]);
		shell->herdoc = false;
		ft_fprintf(1, "\n");
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

void	execute_rdr_heredoc(t_redirect_node *redirect)
{
	int			pipe_read_end;
	t_minishell	*shell;

	shell = minishell_get();
	if (shell->herdoc)
	{
		dup2(shell->filedescriptor.std_in, STDIN_FILENO);
		pipe_read_end = initialize_heredoc(redirect->file);
		dup2(pipe_read_end, STDIN_FILENO);
		close(pipe_read_end);
	}
}

// static char	*null_end_str_heredoc(char **str)
// {
// 	int		i;
// 	char	*rtn;

// 	rtn = *str;
// 	i = 0;
// 	while ((*str)[i] && (*str)[i] != '\n'
// 			&& (*str)[i] != '$' && (*str)[i] != '\''
// 			&& (*str)[i] != '\"')
// 		i++;
// 	rtn = fti_malloc((sizeof(char) * i) + 1, TEMPORARY);
// 	i = 0;
// 	while (**str && **str != '\n'
// 		&& **str != '$' && **str != '\''
// 		&& **str != '\"')
// 	{
// 		rtn[i] = **str;
// 		(*str)++;
// 		i++;
// 	}
// 	rtn[i] = '\0';
// 	return (rtn);
// }

// static unsigned int	strlen_with_expansion_herdoc(char *str)
// {
// 	int		len_1;
// 	int		len_2;
// 	char	*tmp_str;

// 	len_1 = 0;
// 	len_2 = 0;
// 	while (*str)
// 	{
// 		if (*str == '$')
// 		{
// 			str++;
// 			tmp_str = null_end_str_heredoc(&str);
// 			tmp_str = get_environment_value(tmp_str);
// 			if (tmp_str)
// 				len_2 += ft_strlen(tmp_str);
// 		}
// 		if (*str && *str != '$')
// 		{
// 			str++;
// 			len_1++;
// 		}
// 	}
// 	return (len_1 + len_2);
// }

// static char	*expand_heredoc(char *line)
// {
// 	char	*rtn;
// 	char	*tmp_str;
// 	int		i;
// 	int		len;

// 	len = strlen_with_expansion_herdoc(line);
// 	rtn = fti_malloc((sizeof(char) * len) + 1, TEMPORARY);
// 	i = 0;
// 	while (*line)
// 	{
// 		if (*line == '$')
// 		{
// 			line++;
// 			tmp_str = null_end_str_heredoc(&line);
// 			tmp_str = get_environment_value(tmp_str);
// 			while (tmp_str && *tmp_str)
// 			{
// 				rtn[i] = *tmp_str;
// 				tmp_str++;
// 				i++;
// 			}
// 		}
// 		if (*line && *line != '$')
// 		{
// 			rtn[i++] = *line;
// 			line++;
// 		}
// 	}
// 	return (rtn);
// }

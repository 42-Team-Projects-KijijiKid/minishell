#include "minishell.h"

char	*null_end_str_heredoc(char **str)
{
	int		i;
	char	*rtn;

	rtn = *str;
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n'
			&& (*str)[i] != '$' && (*str)[i] != '\''
			&& (*str)[i] != '\"')
		i++;
	rtn = fti_malloc((sizeof(char) * i) + 1, TEMPORARY);
	i = 0;
	while (**str && **str != '\n'
		&& **str != '$' && **str != '\''
		&& **str != '\"')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

unsigned int	strlen_with_expansion_herdoc(char *str)
{
	int		len_1;
	int		len_2;
	char	*tmp_str;

	len_1 = 0;
	len_2 = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			tmp_str = null_end_str_heredoc(&str);
			tmp_str = get_environment_value(tmp_str);
			if (tmp_str)
				len_2 += ft_strlen(tmp_str);
		}
		if (*str && *str != '$')
		{
			str++;
			len_1++;
		}
	}
	return (len_1 + len_2);
}

char	*expand_heredoc(char *line)
{
	char	*rtn;
	char	*tmp_str;
	int		i;
	int		len;

	len = strlen_with_expansion_herdoc(line);
	rtn = fti_malloc((sizeof(char) * len) + 1, TEMPORARY);
	i = 0;
	while (*line)
	{
		if (*line == '$')
		{
			line++;
			tmp_str = null_end_str_heredoc(&line);
			tmp_str =  get_environment_value(tmp_str);
			while (tmp_str && *tmp_str)
			{
				rtn[i] = *tmp_str;
				tmp_str++;
				i++;
			}
		}
		if (*line && *line != '$')
		{
			rtn[i++] = *line;
			line++;
		}
	}
	return (rtn);
}

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
		line = expand_heredoc(line);
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

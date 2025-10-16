#ifndef PARSING_H
# define PARSING_H

typedef struct	s_redir
{
	int		write_fd;
	int		read_fd;
	t_redir	*next;
}	t_redir;

typedef enum	e_token_type
{
	T_TEXT,
	T_PIPE,
	T_AND,
	T_OR,
	T_IN_RDR,
	T_OUT_RDR,
	T_APPEND,
	T_HEREDOC
}	t_token_enum;

typedef struct	s_token
{
	t_token_enum	type;
	char			value;
	t_redir			redirections;

	t_token			*left;
	t_token			*right;
	t_token			*back;
}	t_token;


#endif
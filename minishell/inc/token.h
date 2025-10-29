#ifndef TOKEN_H
# define TOKEN_H

typedef enum	e_redir_type
{
	IN_FD,
	OUT_FD,
	HEREDOC,
	STD
}	t_redir_type;

typedef struct	s_redir
{
	t_redir_type	type;
	int				fd;
	char			*path;
	struct s_redir	*next;
}	t_redir;

typedef	struct	s_redir_meta
{
	t_redir *head;
	t_redir	*tail;
	ssize_t	size;
}	t_redir_meta;


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
	char			**args_2d;
	t_redir_meta	redir_meta;
	
	struct s_token	*left;
	struct s_token	*right;
	struct s_token	*back;
}	t_token;


#endif
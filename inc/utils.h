#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

// integrations/fti_malloc.c
void		*fti_malloc(ssize_t size, t_garbage_layers type);

// integrations/fti_readline.c
char		*fti_readline(char *promt);

// integrations/fti_split.c
char		**fti_split(char const *s, char c);

// integrations/fti_strdup.c
char		*fti_strdup(const char *s, t_garbage_layers layer);

// integrations/fti_strjoin.c
char		*fti_strjoin(char const *s1,
				char const *s2, t_garbage_layers layer);

// integrations/fti_itoa.c
char		*fti_itoa(int n);

// integrations/fti_substr.c
char		*fti_substr(const char *s, unsigned int start, size_t len);

// error.c
void		ft_error(char *msg, char *file, int line, u_int64_t status);
int			print_error(char *msg, unsigned char status);

// garbage.c
void		garbage_free_all(void);

//init_minishell.c
void		minishell_run(void);
t_minishell	*minishell_initialize(char **env);
t_minishell	*minishell_get(void);

// fti_fork.c
int			ft_fork(void);

// read_next_line.c
char		*read_next_line(int fd);

#endif
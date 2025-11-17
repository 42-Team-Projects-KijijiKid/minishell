#ifndef UTILS_H
# define UTILS_H

#include "structs.h"

// integrations/fti_malloc.c
void	*fti_malloc(ssize_t size, e_garbage_layers type);

// integrations/fti_readline.c
char	*fti_readline(char *promt);

// integrations/fti_strdup.c
char	*fti_strdup(const char *s, e_garbage_layers layer);

// integrations/fti_strjoin.c
char	*fti_strjoin(char const *s1, char const *s2);

// error.c
void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat);
void	error_msg(char *msg, char *file, int line);

// garbage.c
void	garbage_free_all(void);

//init_minishell.c
void		run_minishell();
t_minishell	*minishell_initialize(char **env);
t_minishell	*minishell_get(void);


#endif
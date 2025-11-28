#ifndef BUILTINS_H
# define BUILTINS_H

// builtin_cd.c
int		builtin_cd(char **args);

// builtin_cd.c
int		len_until_slash(char *line);
int		count_go_back(char *new_path);
char	*cut_till_slash(char *current_pwd);

// builtin_echo.c
int		builtin_echo(char **args);

// builtin_env.c
int		builtin_env(char **args);

// builtin_exit.c
void	builtin_exit(char **args);

// builtin_export.c
int		builtin_export(char **args);

// builtin_pwd.c
int		builtin_pwd(char **args);

// builtin_unset.c
int		builtin_unset(char **args);

// builtin_export_helpers.c
void	concatenate_env(char *str);
char	*extract_value(char *str);
bool	has_valid_key(char *str);
bool	has_value(char *str);

// builtin_export_helpers_2.c
char	*extract_key(char *str);

// builtin_export_print.c
void	print_sorted_exported(void);

#endif

#ifndef BUILTINS_H
# define BUILTINS_H

// builtin_cd.c
int	builtin_cd(char **args);

// builtin_echo.c
int	builtin_echo(char **args);

// builtin_env.c
int	builtin_env(void);

// builtin_exit.c
int	builtin_exit(char **args);

// builtin_export.c
int	builtin_export(char **args);

// builtin_pwd.c
int	builtin_pwd(char **args);

// builtin_unset.c
int	builtin_unset(char **args);

#endif

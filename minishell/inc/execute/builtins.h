#ifndef BUILTINS_H
# define BUILTINS_H

// builtin_cd.c
void	builtin_cd(char **args);

// builtin_echo.c
void	builtin_echo(char **args);

// builtin_env.c
void	builtin_env(char **args);

// builtin_exit.c
void	builtin_exit(char **args);

// builtin_export.c
void	builtin_export(char **args);

// builtin_pwd.c
void	builtin_pwd(char **args);

// builtin_unset.c
void	builtin_unset(char **args);

#endif

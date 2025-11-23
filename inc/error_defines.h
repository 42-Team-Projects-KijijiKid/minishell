#ifndef ERROR_DEFINES_H
# define ERROR_DEFINES_H


//General
#define SYNTAX_ERROR "syntax error near unexpected token %s\n"
#define TOO_MANY_ARGUMENTS "%s: too many arguments\n"
#define CMD_NOT_FOUND "%s: command not found\n"
#define INFILE_NOT_FOUND "%s: No such file or directory\n"
#define INVALID_ARGS_EXECUTION "Invalid args for command execution\n"

// Redirection 
#define OUTFILE_PERMISSION_DENIED "%s: Permission denied\n"

// LS Command
#define LS_CANNOT_ACCESS "ls: cannot access %s: No such file or directory\n"
#define LS_CANNOT_OPEN "ls: cannot open directory %s: Permission denied\n"
#define LS_INVALID_OPTION "ls: invalid option -- '%s'\n"
// USER DEFINED ERROR MSG's
#define USR_INVALID_SUBSHELL "Invalid subshell usage\n"
#define USR_INVALID_OPERATOR "Invalid operator usage\n"

//EXITING Errors
#define DUP2_FAILED "Failed to duplicate file descriptor for input redirection\n"
#define PIPE_FAILED "Pipe creation failed\n"
#define FORK_FAILED "Fork failed\n"

#endif
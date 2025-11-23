#ifndef ERROR_DEFINES_H
# define ERROR_DEFINES_H


//General
#define SYNTAX_ERROR "syntax error near unexpected token %s\n"
#define TOO_MANY_ARGUMENTS "%s: too many arguments\n"
#define CMD_NOT_FOUND "%s: command not found\n"
#define INFILE_NOT_FOUND "%s: No such file or directory\n"

// LS COMMAND 
#define LS_CANNOT_ACCESS "ls: cannot access %s: No such file or directory\n"
#define LS_CANNOT_OPEN "ls: cannot open directory %s: Permission denied\n"
#define LS_INVALID_OPTION "ls: invalid option -- '%s'\n"
// USER DEFINED ERROR MSG's
#define USR_INVALID_SUBSHELL "Invalid subshell usage\n"
#define USR_INVALID_OPERATOR "Invalid operator usage\n"


#endif
#ifndef shell_h
#define shell_h

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;

struct stat perms;

int simple_shell(void);
void ctrld(void);
int readcheck(ssize_t read, char **line);
void exitcheck(char *command_path, char **array, char *line);
int executor(char *command_path, char **array);
int envcheck(char *command_path);
char *get_path(char *command_path);
int executepath(char *command_path, char **array);

#endif
